#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED显示屏的宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED复位引脚 (ESP32不需要连接复位引脚，所以用-1表示不使用)
#define OLED_RESET    -1

// GY-30和OLED的I2C地址
#define GY30_ADDRESS 0x23
#define OLED_I2C_ADDRESS 0x3C

// 创建Adafruit SSD1306对象，使用Wire1控制OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

// 设备状态结构
struct Device {
    bool on;
    int light;
    int power;
    bool autoMode;
    int kelvin;
    int luminance;
};

// 初始化设备状态
Device device = {false, 0, 50, false, 4000, 400};

// ESP8266 Peer的MAC地址
uint8_t peerAddress[] = {0xCC, 0x50, 0xE3, 0x74, 0xF5, 0x1A};

// ESP-NOW发送回调函数
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// GY-30类定义
class GY30 {
public:
    GY30() {}

    // 初始化GY-30传感器
    void begin() {
        Wire.beginTransmission(GY30_ADDRESS);
        Wire.write(0x01); // 电源开
        Wire.endTransmission();

        Wire.beginTransmission(GY30_ADDRESS);
        Wire.write(0x07); // 复位
        Wire.endTransmission();

        Wire.beginTransmission(GY30_ADDRESS);
        Wire.write(0x10); // 设置连续模式
        Wire.endTransmission();
    }

    // 获取光照强度值
    float getLightLevel() {
        uint16_t data = 0;

        // 读取传感器的2字节数据
        Wire.requestFrom(GY30_ADDRESS, 2);
        if (Wire.available() == 2) {
            data = Wire.read();
            data <<= 8;
            data |= Wire.read();
        }

        // 计算光照值
        float lightLevel = data / 1.2;
        return lightLevel;
    }
};

GY30 gy30;  // 创建GY-30对象

// 初始化Wi-Fi为STA模式
void initWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi initialized in STA mode");
}

// 初始化ESP-NOW
void initESPNow() {
    if (esp_now_init() == ESP_OK) {
        Serial.println("ESP-NOW Initialized");
    } else {
        Serial.println("ESP-NOW Init failed");
        ESP.restart();
    }

    // 注册发送回调
    esp_now_register_send_cb(onSent);

    // 添加Peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    peerInfo.ifidx = WIFI_IF_STA;  // 确保将Peer绑定到STA接口

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    Serial.println("Peer added successfully");
}

// 更新OLED显示
void updateOLED() {
    display.clearDisplay();
    
    // 显示设备状态
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // 显示开关状态
    if (device.on) {
        display.setCursor(0, 0);
        display.print("Light On");
    } else {
        display.setCursor(0, 0);
        display.print("Light Off");
    }

    // 显示光照强度
    display.setCursor(0, 10);
    display.printf("Light: %d Lx", device.light);

    // 显示功率
    display.setCursor(0, 20);
    display.printf("Power: %d %%", device.power);

    // 显示模式
    display.setCursor(0, 30);
    if (device.autoMode) {
        display.print("Auto Mode");
    } else {
        display.print("Manual Mode");
    }

    // 显示色温和亮度
    display.setCursor(0, 40);
    display.printf("Kelvin: %d K", device.kelvin);

    display.setCursor(0, 50);
    display.printf("Luminance: %d lm", device.luminance);

    display.display();  // 更新显示内容
}

// 发送设备数据到ESP8266
void sendESPNowData() {
    // 更新设备的光线强度值
    device.light = (int)gy30.getLightLevel();

    // 创建JSON对象
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["on"] = device.on;
    jsonDoc["light"] = device.light;
    jsonDoc["power"] = device.power;
    jsonDoc["auto"] = device.autoMode;
    jsonDoc["kelvin"] = device.kelvin;
    jsonDoc["luminance"] = device.luminance;

    // 序列化JSON为字符串
    char jsonBuffer[200];
    serializeJson(jsonDoc, jsonBuffer);

    // 通过ESP-NOW发送数据
    esp_err_t result = esp_now_send(peerAddress, (uint8_t *)jsonBuffer, sizeof(jsonBuffer));

    if (result == ESP_OK) {
        Serial.println("Sent successfully");
    } else {
        Serial.println("Error sending the data");
    }
}

void setup() {
    // 初始化串口
    Serial.begin(115200);

    // 初始化GY-30传感器的I2C总线 (SDA: 21, SCL: 19)
    Wire.begin(21, 19);
    gy30.begin();
    Serial.println("GY-30 sensor initialized.");

    // 初始化OLED显示屏的I2C总线 (SDA: 23, SCL: 22)
    Wire1.begin(23, 22);
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);  // 如果初始化失败，则停止
    }
    display.display();
    delay(2000);  // 显示初始化画面
    display.clearDisplay();

    // 初始化Wi-Fi和ESP-NOW
    initWiFi();
    initESPNow();
}

void loop() {
    // 每隔1秒获取并发送光线传感器数据
    float lightLevel = gy30.getLightLevel();
    Serial.print("Light Level: ");
    Serial.print(lightLevel);
    Serial.println(" Lx");

    sendESPNowData();

    // 更新OLED显示
    updateOLED();
    
    delay(1000);
}

#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <ArduinoJson.h>

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

// GY-30 I2C地址
#define GY30_ADDRESS 0x23

class GY30 {
public:
    GY30() {}

    // 初始化GY-30传感器
    void begin() {
        Wire.begin();
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

    // 初始化I2C和GY-30传感器
    Wire.begin(21, 19); // SDA, SCL
    gy30.begin();
    Serial.println("GY-30 sensor initialized.");

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
    delay(1000);
}

#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>    

// 设备状态
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

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

// 发送设备数据到ESP8266
void sendESPNowData() {
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

    // 初始化Wi-Fi和ESP-NOW
    initWiFi();
    initESPNow();
}

void loop() {
    // 每隔1秒发送一次数据
    sendESPNowData();
    delay(1000);
}

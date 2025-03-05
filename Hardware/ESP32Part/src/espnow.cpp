#include "espnow.h"

// ESP-NOW PeerToPeer protocol
//uint8_t peerAddress2[] = {0xCC, 0x50, 0xE3, 0x74, 0xF5, 0x1A};
uint8_t peerAddress[] = {0xCC, 0x50, 0xE3, 0x74, 0xF5, 0x1A};

/* initWiFi Function
 * <> Initializes the WiFi connection for ESP-NOW
 * <> 用于设置WiFi连接，以支持ESP-NOW功能
*/
void initWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi initialized in STA mode");
}

/* onSent Function
 *
 * <> Callback function when data is sent via ESP-NOW
 *
 * <> 数据发送完成后调用的回调函数
 *
 * <> 处理发送状态及相关的设备MAC地址
 *
 * @param mac_addr The MAC address of the device that was sent to
 * @param status The status of the sent data
*/
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

/* initESPNow Function
 * <> Initializes ESP-NOW for communication
 * <> 用于初始化ESP-NOW通信功能
*/
void initESPNow() {
    initWiFi();

    if (esp_now_init() == ESP_OK) {
        Serial.println("ESP-NOW Initialized");
    } else {
        Serial.println("ESP-NOW Init failed");
        ESP.restart();
    }

    esp_now_register_send_cb(onSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    peerInfo.ifidx = WIFI_IF_STA; 

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    Serial.println("Peer added successfully");
/*
    esp_now_peer_info_t peerInfo2;
    memcpy(peerInfo2.peer_addr, peerAddress2, 6);
    peerInfo2.channel = 0;  
    peerInfo2.encrypt = false;
    peerInfo2.ifidx = WIFI_IF_STA; 

    if (esp_now_add_peer(&peerInfo2) != ESP_OK) {
        Serial.println("Failed to add peer2");
        return;
    }
    Serial.println("Peer2 added successfully");
*/    
}

/* sendESPNowData Function
 * <> Sends data using ESP-NOW
 * <> 使用ESP-NOW发送数据
*/
void sendESPNowData() {
    device.lightIntensity = (int)updateGY30();
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["on"] = device.powerStatus;
    jsonDoc["light"] = device.lightIntensity;
    jsonDoc["power"] = device.lumiManual;
    jsonDoc["auto"] = device.modeSwitch;
    jsonDoc["kelvin"] = device.colorTemper;
    jsonDoc["luminance"] = device.lumiAuto;

    char jsonBuffer[200];
    serializeJson(jsonDoc, jsonBuffer);
    esp_err_t result = esp_now_send(peerAddress, (uint8_t *)jsonBuffer, sizeof(jsonBuffer));

    if (result == ESP_OK) {
        Serial.println("Sent successfully");
    } else {
        Serial.println("Error sending the data");
    }
}

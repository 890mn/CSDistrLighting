#include "main.h"

#include "oled.h"
#include "gy30.h"
#include "bluetooth.h"

Device device = {
    /* PowerOFF       */  false,         
    /* Manual Mode    */  false,   
    /* lightIntensity */  0,      
    /* lumiManual     */  50,     
    /* colorTemper    */  4000,      
    /* lumiAuto       */  400    
};

// ESP-NOW PeerToPeer protocol
uint8_t peerAddress[] = {0xCC, 0x50, 0xE3, 0x74, 0xF5, 0x1A};

void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void initWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi initialized in STA mode");
}

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
}

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

void setup() {
    Serial.begin(115200);
    initOLED();
    initGY30();
    initESPNow();
    initBLE("LIGHT-BLE");
}

void loop() {
    sendESPNowData();
    sendBLEData();
    updateOLED(device);
    delay(1000);
}

#include <Arduino.h>
#include "BLEDevice.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include <Wire.h>
#include <WiFi.h>

#define OLED_SDA 21
#define OLED_SCL 22
#define GY30_ADDR 0x23

struct Device {
    bool on;
    int light;
    int power;
    bool auto_mode;
    int kelvin;
    int luminance;
};

Device device = {false, 0, 50, false, 4000, 400};

// Peer address in flash (to save RAM)
const uint8_t peerAddress[] PROGMEM = {0xCC, 0x50, 0xE3, 0x74, 0xF5, 0x1A};

// BLE Server
class BLECallback : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {}
    void onDisconnect(BLEServer* pServer) { pServer->getAdvertising()->start(); }
};

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

void setup_ble() {
    BLEDevice::init("LIGHT-BLE");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new BLECallback());
    BLEService *pService = pServer->createService("6E400000-B5A3-F393-E0A9-E50E24DCCA9E");
    pCharacteristic = pService->createCharacteristic("6E400001-B5A3-F393-E0A9-E50E24DCCA9E",
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_WRITE);
    pService->start();
    pServer->getAdvertising()->start();
}

void setup_espnow() {
    WiFi.mode(WIFI_STA);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

    if (esp_now_init() != ESP_OK) return;

    esp_now_peer_info_t peerInfo = {};
    memcpy_P(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 1;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);
}

void send_espnow_data() {
    char json_buffer[256];
    sprintf(json_buffer, "{\"on\":%d,\"light\":%d,\"power\":%d,\"auto\":%d,\"kelvin\":%d,\"luminance\":%d}",
            device.on, device.light, device.power, device.auto_mode, device.kelvin, device.luminance);
    esp_now_send(peerAddress, (uint8_t *)json_buffer, strlen(json_buffer));
}

class GY30 {
public:
    GY30() { Wire.begin(OLED_SDA, OLED_SCL); }
    void init() {
        Wire.beginTransmission(GY30_ADDR);
        Wire.write(0x01); Wire.endTransmission();
        Wire.beginTransmission(GY30_ADDR);
        Wire.write(0x07); Wire.endTransmission();
        Wire.beginTransmission(GY30_ADDR);
        Wire.write(0x10); Wire.endTransmission();
    }
    uint16_t get_value() {
        Wire.requestFrom(GY30_ADDR, 2);
        if (Wire.available() == 2) {
            return Wire.read() << 8 | Wire.read();  // Removed floating-point division
        }
        return 0;
    }
};

GY30 gy30_sensor;

void loop() {
    device.light = gy30_sensor.get_value();
    send_espnow_data();
    delay(1000);
}

void setup() {
    gy30_sensor.init();
    setup_ble();
    setup_espnow();
}

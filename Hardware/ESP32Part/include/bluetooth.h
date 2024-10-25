#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "main.h"

#define SERVICE_UUID        "6E400000-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"

extern bool deviceConnected;
extern BLECharacteristic *bleCharacteristic;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.println("BLE Connected");
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("BLE Disconnected");
        pServer->getAdvertising()->start();
    }
};

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();

        if (value.length() > 0) {
            Serial.println("Received BLE data:");
            for (int i = 0; i < value.length(); i++) {
                Serial.print(value[i]);
            }
            Serial.println();
            
            // 检查接收到的值是否为 "0"
            if (value == "0") {
                // 如果接收到 "0"，发送当前设备状态，包裹在数组中
                StaticJsonDocument<200> jsonDoc;
                jsonDoc["on"] = device.powerStatus;
                jsonDoc["light"] = device.lightIntensity;
                jsonDoc["power"] = device.lumiManual;
                jsonDoc["auto"] = device.modeSwitch;
                jsonDoc["kelvin"] = device.colorTemper;
                jsonDoc["luminance"] = device.lumiAuto;

                // 创建一个数组，将设备状态包裹在数组中
                StaticJsonDocument<256> arrayDoc;
                JsonArray array = arrayDoc.to<JsonArray>();
                array.add(jsonDoc);  // 将设备状态添加为数组中的第一个元素

                // 序列化数组并发送
                char buffer[256];
                serializeJson(arrayDoc, buffer);

                bleCharacteristic->setValue(buffer);
                bleCharacteristic->notify();
                Serial.println("Sent current device state as JSON array over BLE");

            } else {
                // 解析JSON数据并更新设备状态
                StaticJsonDocument<200> jsonDoc;
                DeserializationError error = deserializeJson(jsonDoc, value);

                if (!error) {
                    device.powerStatus = jsonDoc["on"];
                    device.modeSwitch = jsonDoc["auto"];
                    device.lumiManual = jsonDoc["power"];
                    device.colorTemper = jsonDoc["kelvin"];
                    device.lumiAuto = jsonDoc["luminance"];
                    Serial.println("Device state updated from BLE");
                } else {
                    Serial.println("Failed to parse BLE JSON");
                }
            }
        }
    }
};

void initBLE(const char* name);
void sendBLEData();

#endif
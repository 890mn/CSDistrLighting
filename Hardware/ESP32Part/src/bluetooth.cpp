#include "bluetooth.h"

bool deviceConnected                 = false;
BLEServer *bleServer                 = nullptr;
BLECharacteristic *bleCharacteristic = nullptr;

/* initBLE Function
 *
 * <> Initializes BLE with the given name
 * 
 * <> 根据提供的名称初始化BLE
 * 
 * @param name The name of the BLE device
*/
void initBLE(const char* name) {
    BLEDevice::init(name);
    bleServer = BLEDevice::createServer();
    bleServer->setCallbacks(new MyServerCallbacks());

    BLEService *service = bleServer->createService(SERVICE_UUID);
    bleCharacteristic = service->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_WRITE_NR
                    );
    bleCharacteristic->addDescriptor(new BLE2902());
    bleCharacteristic->setCallbacks(new MyCallbacks());

    service->start();
    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06); 
    advertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("BLE Advertising started");
}

/* sendBLEData Function
 * <> Sends data over BLE
 * <> 通过BLE发送数据
*/
void sendBLEData() {
    if (deviceConnected) {
        StaticJsonDocument<200> jsonDoc;
        jsonDoc["on"] = device.powerStatus;
        jsonDoc["light"] = device.lightIntensity;
        jsonDoc["power"] = device.lumiManual;
        jsonDoc["auto"] = device.modeSwitch;
        jsonDoc["kelvin"] = device.colorTemper;
        jsonDoc["luminance"] = device.lumiAuto;

        char buffer[200];
        serializeJson(jsonDoc, buffer);
        bleCharacteristic->setValue(buffer);
        bleCharacteristic->notify();
        Serial.println("BLE data sent");
    }
}

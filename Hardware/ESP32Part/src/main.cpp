#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define GY30_ADDRESS 0x23
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);

struct Device {
    bool on;
    int light;
    int power;
    bool autoMode;
    int kelvin;
    int luminance;
};

Device device         = {false, 0, 50, false, 4000, 400};
uint8_t peerAddress[] = {0xCC, 0x50, 0xE3, 0x74, 0xF5, 0x1A};

#define SERVICE_UUID        "6E400000-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"

bool deviceConnected                 = false;
BLEServer *bleServer                 = nullptr;
BLECharacteristic *bleCharacteristic = nullptr;

void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

class GY30 {
public:
    void begin() {
        Wire.beginTransmission(GY30_ADDRESS);
        Wire.write(0x01);
        Wire.endTransmission();

        Wire.beginTransmission(GY30_ADDRESS);
        Wire.write(0x07);
        Wire.endTransmission();

        Wire.beginTransmission(GY30_ADDRESS);
        Wire.write(0x10);
        Wire.endTransmission();
    }

    float getLightLevel() {
        uint16_t data = 0;
        Wire.requestFrom(GY30_ADDRESS, 2);
        if (Wire.available() == 2) {
            data = Wire.read();
            data <<= 8;
            data |= Wire.read();
        }
        return data / 1.2;
    }
};

GY30 gy30;

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
                jsonDoc["on"] = device.on;
                jsonDoc["light"] = device.light;
                jsonDoc["power"] = device.power;
                jsonDoc["auto"] = device.autoMode;
                jsonDoc["kelvin"] = device.kelvin;
                jsonDoc["luminance"] = device.luminance;

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
                    device.on = jsonDoc["on"];
                    device.autoMode = jsonDoc["auto"];
                    device.power = jsonDoc["power"];
                    device.kelvin = jsonDoc["kelvin"];
                    device.luminance = jsonDoc["luminance"];
                    Serial.println("Device state updated from BLE");
                } else {
                    Serial.println("Failed to parse BLE JSON");
                }
            }
        }
    }
};

void initWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.println("WiFi initialized in STA mode");
}

void initESPNow() {
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

void sendBLEData() {
    if (deviceConnected) {
        StaticJsonDocument<200> jsonDoc;
        jsonDoc["on"] = device.on;
        jsonDoc["light"] = device.light;
        jsonDoc["power"] = device.power;
        jsonDoc["auto"] = device.autoMode;
        jsonDoc["kelvin"] = device.kelvin;
        jsonDoc["luminance"] = device.luminance;

        char buffer[200];
        serializeJson(jsonDoc, buffer);
        bleCharacteristic->setValue(buffer);
        bleCharacteristic->notify();
        Serial.println("BLE data sent");
    }
}

void updateOLED() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(device.on ? "Light On" : "Light Off");
    display.setCursor(0, 10);
    display.printf("Light: %d Lx", device.light);
    display.setCursor(0, 20);
    display.printf("Power: %d %%", device.power);
    display.setCursor(0, 30);
    display.print(device.autoMode ? "Auto Mode" : "Manual Mode");
    display.setCursor(0, 40);
    display.printf("Kelvin: %d K", device.kelvin);
    display.setCursor(0, 50);
    display.printf("Luminance: %d lm", device.luminance);
    display.display();
}

void sendESPNowData() {
    device.light = (int)gy30.getLightLevel();
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["on"] = device.on;
    jsonDoc["light"] = device.light;
    jsonDoc["power"] = device.power;
    jsonDoc["auto"] = device.autoMode;
    jsonDoc["kelvin"] = device.kelvin;
    jsonDoc["luminance"] = device.luminance;

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

    Wire1.begin(23, 22);
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

    Wire.begin(21, 19);
    gy30.begin();

    initWiFi();
    initESPNow();
    initBLE("LIGHT-BLE");
}

void loop() {
    sendESPNowData();
    sendBLEData();
    updateOLED();
    delay(1000);
}

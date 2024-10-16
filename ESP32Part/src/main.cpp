#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoJson.h>
#include <Adafruit_SSD1306.h>

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

// BLE UUIDs
#define SERVICE_UUID        "6E400000-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"

// BLE变量
BLEServer *bleServer = nullptr;
BLECharacteristic *bleCharacteristic = nullptr;
bool deviceConnected = false;
bool oldDeviceConnected = false;

// LED状态指示
int ledPin = 2;

// BLE服务回调类，处理连接和断开的事件
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        digitalWrite(ledPin, HIGH);  // LED亮起表示设备已连接
        Serial.println("BLE Connected");
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        pServer->startAdvertising();  // 重新广播，等待手机连接
        digitalWrite(ledPin, LOW);    // LED熄灭表示设备已断开连接
        Serial.println("BLE Disconnected");
    }
};

// BLE特性回调类，处理手机端发送的数据
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        
        if (value.length() > 0) {
            Serial.println("Received BLE data:");
            for (int i = 0; i < value.length(); i++) {
                Serial.print(value[i]);
            }
            Serial.println();
            
            // 解析接收到的数据并更新设备状态
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
};

// 初始化BLE
void initBLE(const char* name) {
    BLEDevice::init(name);
    bleServer = BLEDevice::createServer();
    bleServer->setCallbacks(new MyServerCallbacks());

    BLEService *service = bleServer->createService(SERVICE_UUID);
    bleCharacteristic = service->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY |
                        BLECharacteristic::PROPERTY_WRITE
                    );
    bleCharacteristic->addDescriptor(new BLE2902());
    bleCharacteristic->setCallbacks(new MyCallbacks());

    service->start();

    // 设置MTU，最大传输单元
    BLEDevice::setMTU(185);

    // 启动广播，让手机能发现
    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06);  // 使能BLE广播
    advertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("BLE Advertising started");
}

// 通过BLE发送设备状态
void sendBLEData() {
    if (deviceConnected) {
        // 将设备状态序列化为JSON数组
        StaticJsonDocument<200> jsonDoc;
        JsonArray arr = jsonDoc.to<JsonArray>();  // 创建JSON数组
        JsonObject obj = arr.createNestedObject();  // 创建数组中的对象
        obj["on"] = device.on;
        obj["light"] = device.light;
        obj["power"] = device.power;
        obj["auto"] = device.autoMode;
        obj["kelvin"] = device.kelvin;
        obj["luminance"] = device.luminance;

        char buffer[200];
        serializeJson(jsonDoc, buffer);

        // 打印发送的数据到串口
        Serial.print("Sending data: ");
        Serial.println(buffer);  // 调试用，打印要发送的数据

        // 通过BLE发送数据
        bleCharacteristic->setValue(buffer);
        bleCharacteristic->notify();  // 使用notify()发送数据
        Serial.println("BLE data sent");
    }
}

void setup() {
    Serial.begin(115200);

    // 初始化LED引脚，指示连接状态
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // 初始化BLE
    initBLE("ESP32-BLE");
}

void loop() {
    // 通过BLE发送设备状态
    if (deviceConnected) {
        sendBLEData();
        delay(1000);  // 每秒发送一次设备状态
    }
    
    // 处理设备连接状态的变化
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // 避免短暂的断开重连
        oldDeviceConnected = deviceConnected;
    }
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
}

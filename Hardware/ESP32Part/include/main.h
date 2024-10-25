#ifndef __MAIN_H
#define __MAIN_H

#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include <ArduinoJson.h>
struct Device {
    bool on;       //< 设备开关状态
    bool autoMode; //< 自动调光模式

    int light;     //< 传感器光强(lx)
    int power;     //< 设备亮度(无自动调光模式下)
    int kelvin;    //< 设备色温
    int luminance; //< 恒定照度(自动调光模式下)
};

#endif
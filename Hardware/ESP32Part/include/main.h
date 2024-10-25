#ifndef __MAIN_H
#define __MAIN_H

#include <Wire.h>
#include <ArduinoJson.h>

struct Device {
    /* <> PowerON - True / PowerOFF - False 
     * <> 设备开关状态 
     * <> Web -[BLE]-> ESP32 -[ESP-NOW]-> ESP8266
     */ 
    bool powerStatus;  
    
    /* <> Auto Mode - True / Manual Mode - False
     * <> 模式切换 对应自动/手动调光模式
     * <> Web -[BLE]-> ESP32
     */ 
    bool modeSwitch;

    /* <> 1 - 65535(16-bit) [Lx]
     * <> 由传感器捕捉的环境光强
     * <> GY30 -[I2C]-> ESP8266
     */ 
    int lightIntensity;

    /* <> 0 - 100 [%]
     * <> Luminance IN Manual Mode 设备亮度[手动调光模式]
     * <> Web -[BLE]-> ESP32
     */
    int lumiManual;

    /* <> 2700 - 6500 [K]
     * <> Color Temperature 设备色温
     * <> Web -[BLE]-> ESP32
     */
    int colorTemper;

    /* <> 300 - 500 [lm]
     * <> Luminance IN Auto Mode 恒定照度[自动调光模式]
     * <> Web -[BLE]-> ESP32
     */
    int lumiAuto;
};
extern Device device;

#endif
#include "main.h"
#include "oled.h"
#include "gy30.h"
#include "espnow.h"
#include "bluetooth.h"

/* Device Structure
 * <> Device structure to hold various device settings
 * <> 包含电源状态、手动模式、光照强度等变量
*/
Device device = {
    /* PowerOFF       */  false,         
    /* Manual Mode    */  false,   
    /* lightIntensity */  0,      
    /* lumiManual     */  50,     
    /* colorTemper    */  4000,      
    /* lumiAuto       */  400    
};

/* setup Function
 * <> Initializes the device settings and components
 * <> 初始化串口、OLED显示器、GY30传感器等
 * <> Setup function is called once at startup
*/
void setup() {
    Serial.begin(115200);
    esp_log_level_set("*", ESP_LOG_INFO);
    initOLED();
    initGY30();
    initESPNow();
    initBLE("LIGHT-BLE");
}

/* loop Function
 * <> Main loop for handling data sending and updating display
 * <> 发送数据和更新OLED显示器的循环
 * <> Continuous execution every 1000 milliseconds
*/
void loop() {
    sendESPNowData();
    sendBLEData();
    updateOLED(device);
    delay(1000);
}

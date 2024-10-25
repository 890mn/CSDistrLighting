#include "main.h"
#include "oled.h"
#include "gy30.h"
#include "espnow.h"
#include "bluetooth.h"

Device device = {
    /* PowerOFF       */  false,         
    /* Manual Mode    */  false,   
    /* lightIntensity */  0,      
    /* lumiManual     */  50,     
    /* colorTemper    */  4000,      
    /* lumiAuto       */  400    
};

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

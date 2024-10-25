#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);

/* initOLED Function
 * <> Initializes the OLED display
 * <> 初始化OLED显示屏
*/
void initOLED() {
    Wire1.begin(23, 22);
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
}

/* updateOLED Function
 *
 * <> Updates the OLED display with the current device state
 * 
 * <> 更新OLED显示屏以显示当前设备状态
 * 
 * @param device The device structure containing state information
*/
void updateOLED(Device device) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(device.powerStatus ? "Light On" : "Light Off");
    display.setCursor(0, 10);
    display.printf("LightInten: %d Lx", device.lightIntensity);
    display.setCursor(0, 20);
    display.printf("lumiManual: %d %%", device.lumiManual);
    display.setCursor(0, 30);
    display.print(device.modeSwitch ? "Auto Mode" : "Manual Mode");
    display.setCursor(0, 40);
    display.printf("ColorTemper: %d K", device.colorTemper);
    display.setCursor(0, 50);
    display.printf("LumiAuto: %d lm", device.lumiAuto);
    display.display();
}

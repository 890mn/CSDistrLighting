#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);

void initOLED() {
    Wire1.begin(23, 22);
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
}

void updateOLED(Device device) {
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
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LDR_PIN 4 // 光敏电阻引脚

// 创建OLED对象，使用地址0x7A
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);
    
    // 初始化 OLED
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // 无法初始化，停在这里
    }

    display.clearDisplay(); // 清空屏幕
}

void loop() {
    int ldrValue = analogRead(LDR_PIN); // 读取光敏电阻的值

    // 清空屏幕并显示新值
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Light Intensity: ");
    display.println(ldrValue); // 显示光强度值
    display.display(); // 刷新显示

    delay(200); // 每秒读取一次
}

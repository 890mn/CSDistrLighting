#ifndef __OLED_H
#define __OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "main.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_ADDRESS 0x3C

void initOLED();
void updateOLED(Device device);

#endif
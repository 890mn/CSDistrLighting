#ifndef __OLED_H
#define __OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "main.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_ADDRESS 0x3C

/* initOLED Function
 * <> Initializes the OLED display
 * <> 初始化OLED显示屏
*/
void initOLED();

/* updateOLED Function
 *
 * <> Updates the OLED display with the current device state
 *
 * <> 更新OLED显示屏以显示当前设备状态
 * 
 * @param device The device structure containing state information
*/
void updateOLED(Device device);

#endif

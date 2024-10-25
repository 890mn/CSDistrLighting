#ifndef __WS2812_H
#define __WS2812_H

#include <Adafruit_NeoPixel.h>
#include "main.h"

extern Adafruit_NeoPixel strip;

/* setPower Function
 *
 * <> 设置灯光的亮度
 * 
 * <> Sets brightness of the light
 * 
 * @param P 亮度值，范围0到255
 * @note 该函数将亮度值应用到灯带的所有灯珠
 */
void setPower(uint8_t P);

/* setRGB Function
 *
 * <> 设置RGB灯带的颜色
 *
 * <> Sets RGB color for the LED strip
 * 
 * @param red 红色通道值
 * @param green 绿色通道值
 * @param blue 蓝色通道值
 * @note 该函数将RGB颜色设置为灯带中的所有像素
 */
void setRGB(uint8_t red, uint8_t green, uint8_t blue);

/* On Function
 * 
 * <> 打开灯光
 * 
 * <> Turns on the light
 * 
 * @note 设置亮度为100%，并应用当前RGB颜色到灯带
 */
void On();

/* Off Function
 * 
 * <> 关闭灯光
 * 
 * <> Turns off the light
 * 
 * @note 将灯光亮度设置为0并关闭所有像素的颜色
 */
void Off();

#endif
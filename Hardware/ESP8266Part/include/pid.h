#ifndef __PID_H
#define __PID_H

#include <PID_v1.h>
#include "main.h"

extern double Input;
extern double Output; 
extern double Setpoint; 

extern PID myPID; 

/* kelvinToRGB Function
 * 
 * <> 将色温（Kelvin）转换为RGB值
 * 
 * <> Converts color temperature (Kelvin) to RGB values
 * 
 * @param K 色温，范围为2700K至6500K
 * @note 该函数将颜色温度转换为对应的RGB值，并将结果存储在全局变量R、G、B中
 */
void kelvinToRGB(uint16_t K);

#endif
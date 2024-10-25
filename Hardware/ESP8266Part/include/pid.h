#ifndef __PID_H
#define __PID_H

#include "main.h"

extern double Input;
extern double Output; 
extern double Setpoint; 

extern PID myPID; 

void kelvinToRGB(uint16_t K);

#endif
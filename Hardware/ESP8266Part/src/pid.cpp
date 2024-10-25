#include "pid.h"

double Input;	  // 当前环境光强度
double Output;	  // 控制灯光亮度
double Setpoint;  // 期望的光强度
double Kp = 0.02; // 比例系数
double Ki = 0.05; // 积分系数
double Kd = 0.01; // 微分系数
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); 

double smoothOutput = 0; // 平滑输出值，用于减缓输出波动
double alpha = 0.2;		 // 平滑系数，用于输出值的滤波

/* kelvinToRGB Function
 * 
 * <> 将色温（Kelvin）转换为RGB值
 * 
 * <> Converts color temperature (Kelvin) to RGB values
 * 
 * @param K 色温，范围为2700K至6500K
 * @note 该函数将颜色温度转换为对应的RGB值，并将结果存储在全局变量R、G、B中
 */
void kelvinToRGB(uint16_t K) 
{
	if (K < 2700 || K > 6500) {
		return;
	}

	float temp = K / 100.0;
	float red, green, blue;

	if (temp <= 66) {
		red = 255;
		green = temp;
		green = 99.4708025861 * log(green) - 161.1195681661;

		if (temp <= 19) {
			blue = 0;
		}
		else {
			blue = temp - 10;
			blue = 138.5177312231 * log(blue) - 305.0447927307;
		}
	}
	else {
		red = temp - 60;
		red = 329.698727446 * pow(red, -0.1332047592);
		green = temp - 60;
		green = 288.1221695283 * pow(green, -0.0755148492);
		blue = 255;
	}

	// 确保RGB值在0-255范围内
	R = constrain(red, 0, 255);
	G = constrain(green, 0, 255);
	B = constrain(blue, 0, 255);
}
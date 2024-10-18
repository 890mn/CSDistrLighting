/**
 * @file  main.cpp
 * @brief 基于ESP8266的智能灯光控制系统，支持ESP-NOW通信，RGB LED灯带控制和PID调节
 */

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <PID_v1.h>

#define NUMPIXELS 24 ///< 灯珠数量
#define PIN 4		 ///< 灯珠连接的IO引脚
#define DEADBAND 5	 ///< PID控制的死区范围

uint8_t R = 0; ///< 红色通道初始值
uint8_t G = 0; ///< 绿色通道初始值
uint8_t B = 0; ///< 蓝色通道初始值

bool previousState = false; ///< 记录设备之前的开关状态
bool isAuto = false;		///< 是否为自动模式
bool isOn = false;			///< 当前设备是否打开

uint16_t light = 0;		  ///< 当前环境光强度
uint8_t power = 50;		  ///< 灯光亮度（0-100）
uint16_t kelvin = 4000;	  ///< 色温（K）
uint16_t luminance = 400; ///< 目标亮度

// PID控制参数
double Input;											   ///< 输入值，即当前环境光强度
double Output;											   ///< PID控制输出值，用于控制灯光亮度
double Setpoint;										   ///< 目标值，即期望的光强度
double Kp = 0.02;										   ///< PID控制器的比例系数
double Ki = 0.05;										   ///< PID控制器的积分系数
double Kd = 0.01;										   ///< PID控制器的微分系数
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); ///< PID控制器对象

double smoothOutput = 0; ///< 平滑输出值，用于减缓输出波动
double alpha = 0.2;		 ///< 平滑系数，用于输出值的滤波

StaticJsonDocument<185> doc; ///< 用于处理接收的JSON数据

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); ///< RGB灯带控制对象

/**
 * @brief 将色温（Kelvin）转换为RGB值
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

/**
 * @brief 设置灯光的亮度
 * @param P 亮度值，范围0到255
 * @note 该函数将亮度值应用到灯带的所有灯珠
 */
void setPower(uint8_t P)
{
	strip.setBrightness(P);
}

/**
 * @brief 设置RGB灯带的颜色
 * @param red 红色通道值
 * @param green 绿色通道值
 * @param blue 蓝色通道值
 * @note 该函数将RGB颜色设置为灯带中的所有像素
 */
void setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
	for (int i = 0; i < NUMPIXELS; ++i) {
		strip.setPixelColor(i, R, G, B);
	}
}

/**
 * @brief 打开灯光
 * @note 设置亮度为100%，并应用当前RGB颜色到灯带
 */
void On()
{
	setPower(100);
	setRGB(R, G, B);
	strip.show();
}

/**
 * @brief 关闭灯光
 * @note 将灯光亮度设置为0并关闭所有像素的颜色
 */
void Off()
{
	setPower(0);
	setRGB(0, 0, 0);
	strip.show();
}

/**
 * @brief 接收到ESP-NOW数据时的回调函数
 * @param mac 发送者的MAC地址
 * @param incomingData 接收到的数据
 * @param len 数据长度
 * @note 当从其他设备接收到数据时，该函数会自动调用，并尝试解析JSON数据
 */
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
	Serial.print("Received: ");
	for (int i = 0; i < len; ++i) {
		Serial.printf("%c", *(incomingData + i));
	}
	Serial.println();

	// 反序列化接收到的JSON数据
	DeserializationError error = deserializeJson(doc, incomingData, len);

	if (!error) {
		isOn = doc["on"];
		light = doc["light"];
		power = doc["power"];
		isAuto = doc["auto"];
		kelvin = doc["kelvin"];
		luminance = doc["luminance"];
		Input = light;
		Setpoint = luminance;

		if (isOn != previousState) {
			isOn ? On() : Off();
			previousState = isOn;
		}
	}
	else {
		Serial.print("deserializeJson() failed: ");
		Serial.println(error.c_str());
	}
}

/**
 * @brief 初始化系统，包括ESP-NOW、串口通信和RGB灯带
 * @note 该函数会设置PID控制器的模式，初始化ESP-NOW通信并设置回调函数
 */
void setup()
{
	Serial.begin(115200);

	// 初始化PID控制器
	myPID.SetMode(AUTOMATIC);
	myPID.SetSampleTime(1000); // 采样周期为1秒

	kelvinToRGB(kelvin);
	WiFi.mode(WIFI_STA); // 设置WIFI为STA模式
	WiFi.disconnect();	 // 断开WiFi连接

	// 初始化ESP-NOW
	if (esp_now_init() != 0) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}
	Serial.println("esp_now init success");

	// 注册接收回调函数
	esp_now_register_recv_cb(OnDataRecv);

	strip.begin(); // 初始化灯带
}

/**
 * @brief 主循环函数，处理自动和手动模式的灯光控制
 * @note 当设备处于打开状态时，该函数会根据模式执行自动或手动控制
 */
void loop()
{
	delay(1000);

	if (isOn) {
		if (isAuto) {
			myPID.Compute();  // 进行PID计算
			setPower(Output); // 根据PID输出设置灯光亮度
		}
		else {
			setPower(map(power, 0, 100, 0, 255)); // 手动模式下的亮度设置
		}

		kelvinToRGB(kelvin); // 设置颜色温度对应的RGB值
		setRGB(R, G, B);
		strip.show();
	}
}

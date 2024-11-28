#include "main.h"
#include "pid.h"
#include "ws2812.h"
#include "espnow_8266.h"

// 呼吸灯控制相关变量
int breathePWM = 0;    // 当前 PWM 值
int breatheDirection = 1; // 呼吸方向：1 表示变亮，-1 表示变暗
const int breatheStep = 2; // 每次调整的 PWM 值步长
const int breatheMin = 0;  // 最小亮度
const int breatheMax = 255; // 最大亮度
const int breatheDelay = 10; // 呼吸灯每步的延时（毫秒）

/* setup Function
 * 
 * <> 初始化系统，包括ESP-NOW、串口通信和RGB灯带
 * 
 * <> Initializes system, including ESP-NOW, serial communication, and RGB LED strip
 * 
 * @note 该函数会设置PID控制器的模式，初始化ESP-NOW通信并设置回调函数
 */
void setup()
{
	Serial.begin(115200);

	// 初始化PID控制器
	myPID.SetMode(AUTOMATIC);
	myPID.SetSampleTime(1000); // 采样周期为1秒

	kelvinToRGB(device.colorTemper);
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

/* loop Function
 * 
 * <> 主循环函数，处理自动和手动模式的灯光控制
 * 
 * <> Main loop to manage light control in automatic and manual modes
 * 
 * @note 当设备处于打开状态时，该函数会根据模式执行自动或手动控制
 */
void loop()
{
    // 输出 PWM 信号
    analogWrite(D2, 100);

	delay(100);

	if (device.modeSwitch) {
		if (device.powerStatus) {
			myPID.Compute();  // 进行PID计算
			setPower(Output); // 根据PID输出设置灯光亮度
		}
		else {
			setPower(map(device.lumiManual, 0, 100, 0, 255)); // 手动模式下的亮度设置
		}

		kelvinToRGB(device.colorTemper); // 设置颜色温度对应的RGB值
		setRGB(R, G, B);
		strip.show();
	}
}

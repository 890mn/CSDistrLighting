#include "main.h"
#include "pid.h"
#include "ws2812.h"

/* Device Structure
 * <> Device structure to hold various device settings
 * <> 包含电源状态、手动模式、光照强度等变量
*/
Device device = {
    /* PowerOFF       */  false,         
    /* Manual Mode    */  false,   
    /* lightIntensity */  0,      
    /* lumiManual     */  50,     
    /* colorTemper    */  4000,      
    /* lumiAuto       */  400    
};
StaticJsonDocument<185> doc;
bool previousState = false; 

/* OnDataRecv Function
 * 
 * <> 接收到ESP-NOW数据时的回调函数
 * 
 * <> Callback function for received ESP-NOW data
 * 
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
		device.modeSwitch = doc["on"];
		device.lightIntensity = doc["light"];
		device.lumiManual = doc["power"];
		device.powerStatus = doc["auto"];
		device.colorTemper = doc["kelvin"];
		device.lumiAuto = doc["luminance"];
		Input = device.lightIntensity;
		Setpoint = device.lumiAuto;

		if (device.modeSwitch != previousState) {
			device.modeSwitch ? On() : Off();
			previousState = device.modeSwitch;
		}
	}
	else {
		Serial.print("deserializeJson() failed: ");
		Serial.println(error.c_str());
	}
}

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
	delay(1000);

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

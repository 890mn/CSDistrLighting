#include "main.h"
#include "pid.h"

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

uint8_t R = 0, G = 0, B = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); 

/* setPower Function
 *
 * <> 设置灯光的亮度
 * 
 * <> Sets brightness of the light
 * 
 * @param P 亮度值，范围0到255
 * @note 该函数将亮度值应用到灯带的所有灯珠
 */
void setPower(uint8_t P)
{
	strip.setBrightness(P);
}

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
void setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
	for (int i = 0; i < NUMPIXELS; ++i) {
		strip.setPixelColor(i, R, G, B);
	}
}

/* On Function
 * 
 * <> 打开灯光
 * 
 * <> Turns on the light
 * 
 * @note 设置亮度为100%，并应用当前RGB颜色到灯带
 */
void On()
{
	setPower(100);
	setRGB(R, G, B);
	strip.show();
}

/* Off Function
 * 
 * <> 关闭灯光
 * 
 * <> Turns off the light
 * 
 * @note 将灯光亮度设置为0并关闭所有像素的颜色
 */
void Off()
{
	setPower(0);
	setRGB(0, 0, 0);
	strip.show();
}

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

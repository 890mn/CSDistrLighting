#include "espnow_8266.h"

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
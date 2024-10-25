#ifndef __ESPNOW_8266_H
#define __ESPNOW_8266_H

#include "main.h"

#include <espnow.h>
#include <ArduinoJson.h>

#include "ws2812.h"
#include "pid.h"

extern Device device;

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
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len);

#endif

#ifndef __ESPNOW_H
#define __ESPNOW_H

#include <WiFi.h>
#include <esp_now.h>

#include "main.h"
#include "gy30.h"

/* initWiFi Function
 * <> Initializes the WiFi connection for ESP-NOW
 * <> 用于设置WiFi连接，以支持ESP-NOW功能
*/
void initWiFi();

/* onSent Function
 *
 * <> Callback function when data is sent via ESP-NOW
 *
 * <> 数据发送完成后调用的回调函数
 *
 * <> 处理发送状态及相关的设备MAC地址
 *
 * @param mac_addr The MAC address of the device that was sent to
 * @param status The status of the sent data
*/
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status);

/* initESPNow Function
 * <> Initializes ESP-NOW for communication
 * <> 用于初始化ESP-NOW通信功能
*/
void initESPNow();

/* sendESPNowData Function
 * <> Sends data using ESP-NOW
 * <> 使用ESP-NOW发送数据
*/
void sendESPNowData();

#endif

#ifndef __ESPNOW_H
#define __ESPMOW_H

#include <WiFi.h>
#include <esp_now.h>

#include "main.h"
#include "gy30.h"

void initWiFi();
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void initESPNow();
void sendESPNowData();

#endif
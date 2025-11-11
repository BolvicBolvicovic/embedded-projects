#ifndef METEO_H
#define METEO_H

#include <ESP8266WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "stddef32.h"

#define SERIAL_BAUDRATE	115200
#define PRINT(a)		Serial.print(a)
#define PRINTLN(a)		Serial.println(a)

const char*	server_path = "https://api.open-meteo.com/v1/forecast?latitude=57.7072326&longitude=11.9670171&current=temperature_2m";

#endif

#ifndef METEO_H
#define METEO_H

#include <ESP8266WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "stddef32.h"

#define SERIAL_BAUDRATE	115200
#define PRINT(a)		Serial.print(a)
#define PRINTLN(a)		Serial.println(a)

const char*	server_root = "http://192.168.68.127:8000/";
const u8*	payload		= (u8*)
	"{\n"
	"	\"temp\": 3.5"
	"}\n";

#endif

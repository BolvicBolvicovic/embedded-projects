#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "stddef32.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // Definiera om den inte finns
#endif
#define SERIAL_BAUDRATE	115200

#define TIMEOUT			2000

const String off_response=
			"HTTP/1.1 200 OK\r\n"
			"Content-type:text/html\r\n"
			"Connection: close\r\n\r\n"
			"<!DOCTYPE html><html>"
			"<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
			"<link rel=\"icon\" href=\"data:,\">"
			"<style>html{font-family:Helvetica;display:inline-block;margin:0 auto;text-align:center;}"
			".button{background-color:#195B6A;border:none;color:white;padding:16px 40px;"
			"text-decoration:none;font-size:30px;margin:2px;cursor:pointer;}</style>"
			"<body><h1>ESP8266 Web Server</h1>"
			"<p>LED - State off</p>"
			"<p><a href=\"/on\"><button class=\"button\">ON</button></a></p>"
			"</body></html>";

const String on_response=
			"HTTP/1.1 200 OK\r\n"
			"Content-type:text/html\r\n"
			"Connection: close\r\n\r\n"
			"<!DOCTYPE html><html>"
			"<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
			"<link rel=\"icon\" href=\"data:,\">"
			"<style>html{font-family:Helvetica;display:inline-block;margin:0 auto;text-align:center;}"
			".button{background-color:#77878A;border:none;color:white;padding:16px 40px;"
			"text-decoration:none;font-size:30px;margin:2px;cursor:pointer;}</style>"
			"<body><h1>ESP8266 Web Server</h1>"
			"<p>LED - State on</p>"
			"<p><a href=\"/off\"><button class=\"button\">OFF</button></a></p>"
			"</body></html>";

#endif

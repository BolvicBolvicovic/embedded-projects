#include "stddef32.h"
#include <EEPROM.h>

#define SERIAL_BAUDRATE	115200
#define EEPROM_SIZE		128
#define SSID_ADDR		0
#define PASS_ADDR		64

void
writeToEeprom(i32 addr, const String& val)
{
	for (i32 i = 0; i < val.length(); i++)
	{
		EEPROM.write(addr + i, val[i]);
		i++;
	}

	EEPROM.write(addr + val.length(), 0);
	EEPROM.commit();
}

String
readFromEeprom(i32 addr)
{
	String	res = "";
	i32		i	= -1;

	do
	{
		i++;
		res += (i8)EEPROM.read(addr + i);
	}
	while(res[i] && i < EEPROM_SIZE);
	res.remove(i);
	
	return res;
}

String
readFromEeprom(i32 addr, i32 len)
{
	String	res = "";

	for (i32 i = 0; i < len; i++)
	{
		res += (i8)EEPROM.read(addr + i);
	}

	return res;
}

void
setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	delay(100);
	Serial.println("\nEEPROM example");

	EEPROM.begin(EEPROM_SIZE);

	String	demo_ssid	= "iotID";
	String	demo_pass	= "iotPass";

	Serial.println("Scriver till EEPROM");
	Serial.println(demo_ssid);
	Serial.println(demo_pass);
	writeToEeprom(SSID_ADDR, demo_ssid);
	writeToEeprom(PASS_ADDR, demo_pass);

	Serial.println("Reset values");
	demo_ssid = "";
	demo_pass = "";
	Serial.println(demo_ssid);
	Serial.println(demo_pass);

	Serial.println("Läser från EEPROM");
	demo_ssid = readFromEeprom(SSID_ADDR);
	demo_pass = readFromEeprom(PASS_ADDR);
	Serial.println(demo_ssid);
	Serial.println(demo_pass);

	Serial.println("Setup DONE");
}

void
loop()
{
}

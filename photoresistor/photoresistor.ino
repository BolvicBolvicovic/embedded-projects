#include "../stddef32.h"

#define SERIAL_BAUD 115200
#define LED_PIN 	D2
#define LDR_PIN		A0

void
setup()
{
	Serial.begin(SERIAL_BAUD);
	pinMode(LED_PIN, OUTPUT);
	pinMode(LDR_PIN, INPUT);
}

void
loop()
{
	i32	value = analogRead(LDR_PIN);

	Serial.print("Analog value: ");
	Serial.println(value);

	if (value > 450)
	{
		digitalWrite(LED_PIN, LOW);
	}
	else
	{
		digitalWrite(LED_PIN, HIGH);
	}
}

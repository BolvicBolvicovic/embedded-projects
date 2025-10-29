#include <DHT11.h>

#define SERIAL_BAUD 115200
#define LED_PIN 	D2
#define DHT11_PIN	D4
#define DHT11_DELAY	1000

DHT11	dht(DHT11_PIN);

void
setup()
{
	Serial.begin(SERIAL_BAUD);
	pinMode(LED_PIN, OUTPUT);
	dht.setDelay(DHT11_DELAY);
}

void
loop()
{
	Serial.print("Temperature: ");
	Serial.println(dht.readTemperature());
	Serial.print("Humidity: ");
	Serial.println(dht.readHumidity());
}

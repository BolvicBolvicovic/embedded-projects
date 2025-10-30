#define SERIAL_BAUDRATE	115200
#define RELAY_PIN		D1

void
setup()
{
	pinMode(RELAY_PIN, OUTPUT);
}

void
loop()
{
	digitalWrite(RELAY_PIN, HIGH);
	delay(500);
	digitalWrite(RELAY_PIN, LOW);
	delay(500);
}

#define SERIAL_BAUDRATE	115200
#define EXTERNAL_LED	D2

void
setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	pinMode(EXTERNAL_LED, OUTPUT);
	Serial.println("Setup DONE");
}

void
loop()
{
	digitalWrite(EXTERNAL_LED, LOW);
	Serial.println("LED OFF");
	delay(500);
	digitalWrite(EXTERNAL_LED, HIGH);
	Serial.println("LED ON");
	delay(500);
}

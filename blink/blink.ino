void
setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.println("Setup DONE");
}

void
loop()
{
	digitalWrite(LED_BUILTIN, LOW);
	Serial.println("LED ON");
	delay(500);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.println("LED OFF");
	delay(500);
}

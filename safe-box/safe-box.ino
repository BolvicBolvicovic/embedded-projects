#include <Encoder.h>
#include "../stddef32.h"

#define SERIAL_BAUDRATE	115200

#define BUTTON_PIN		D5
#define RELAY_PIN		D1
#define BUZZER_PIN		D2

#define CODE_LENGTH		3

Encoder	dial(D7, D6);

// TODO: Upgrade hard coded into decidable code
i32	code[CODE_LENGTH]	= { 2, 4, 6 };
i32	step_idx			= 0;
i32	position			= 0;

void
setup()
{
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(RELAY_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);

	digitalWrite(RELAY_PIN, LOW);
	Serial.begin(SERIAL_BAUDRATE);
}

void
loop()
{
	i32	new_pos = dial.read() / 4;

	if (new_pos != position)
	{
		position = new_pos;
		Serial.print("Dial: ");
		Serial.println(position);
	}

	if (digitalRead(BUTTON_PIN) == LOW)
	{
		if (position == code[step_idx])
		{
			tone(BUZZER_PIN, 800, 100);
			step_idx++;

			if (step_idx == CODE_LENGTH)
			{
				digitalWrite(RELAY_PIN, HIGH);
				tone(BUZZER_PIN, 1200, 300);
				delay(5000);
				digitalWrite(RELAY_PIN, LOW);
				step_idx = 0;
			}
		}
		else
		{
			tone(BUZZER_PIN, 200, 300);
			step_idx = 0;
		}
	}
	

	delay(300);
}

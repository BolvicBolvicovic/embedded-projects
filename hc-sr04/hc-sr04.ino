// Formula to calculate a distance based on ultra sonic waves:
// D = 1/2 × T × C
// where D is the distance, T is the time between the Emission and Reception, and C is the sonic speed.
// (The value is multiplied by 1/2 because T is the time for go-and-return distance.)

#define SERIAL_BAUDRATE	115200
#define TRIGGER_PIN		D5
#define ECHO_PIN		D6

#define TC				0.034
#define CALC_DIST(d)	(d * TC / 2)

long	duration;
int		distance;

void
setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	Serial.println("Setup DONE");
}

void
loop()
{
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(2);


	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN, LOW);

	duration = pulseIn(ECHO_PIN, HIGH);
	distance = CALC_DIST(duration);

	Serial.print("Distance: ");
	Serial.println(distance);
	delay(500);
}

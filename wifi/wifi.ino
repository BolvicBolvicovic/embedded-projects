#include "config.h"

WiFiServer	server(80);
String		led_state		= "off";
String		header			= "";
u32			current_time	= 0;
u32			last_activity	= 0;
i8			c;

void
setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	WiFi.begin(SSID, PASSWORD);
	Serial.print("Connecting");
	
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println();

	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());

	server.begin();

	Serial.println("Setup DONE");
}

void
loop()
{
	WiFiClient	client = server.accept();

	if (client)
	{
		header			= "";
		current_time	= millis();
		last_activity	= current_time;

		while (client.connected() && current_time - last_activity <= TIMEOUT)
		{
			if (client.available())
			{
				c				= client.read();
				last_activity	= current_time;
				current_time	= millis();
				header			+= c;

				if (c == '\n')
				{
					if (header.endsWith("\r\n\r\n"))
					{
						Serial.println("Full header:");
						Serial.println(header);
						if (header.indexOf("GET /on") >= 0)
						{
							digitalWrite(LED_BUILTIN, LOW);
							led_state = "on";
						}
						else if (header.indexOf("GET /off") >= 0)
						{
							digitalWrite(LED_BUILTIN, HIGH);
							led_state = "off";
						}

						if (led_state == "off")
						{
							client.print(off_response);
						}
						else
						{
							client.print(on_response);
						}

						Serial.println("Response sent");
						break;
					}
				}
			}
		}

		client.stop();
		Serial.println("Client Disconnected");
	}
}

#include "config.h"

WiFiServer	server(80);
String		led_state		= "off";
String		header			= "";
u32			current_time	= 0;
u32			last_activity	= 0;
i8			c;

void
configModeCallback (WiFiManager *myWiFiManager)
{
  Serial.println("Gick in i konfigurationsläge");
  Serial.print("Anslut till Wi-Fi: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.println("Öppna IP: 192.168.4.1 i din webbläsare");
 
  // Blinka lysdioden snabbt för att visa att vi är i config-läge
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 20; i++)
  {
    digitalWrite(LED_BUILTIN, LOW); // Tänd
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH); // Släck
    delay(50);
  }
}

void
setup()
{
	Serial.begin(SERIAL_BAUDRATE);
	Serial.println("\nStartar...");
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH); // Håll den släckt (LOW = tänd)
	
	// Skapa en WiFiManager-instans
	WiFiManager wifiManager;
	
	// Ställ in en timeout för konfigurationsportalen (3 minuter)
	// Om ingen ansluter till portalen inom 3 min, startar den om.
	wifiManager.setConfigPortalTimeout(180);
	
	// Sätt en funktion som anropas när portalen startar (se ovan)
	wifiManager.setAPCallback(configModeCallback);
	
	// Detta är namnet på Wi-Fi-nätverket som din ESP8266 skapar
	String apName = "ESP8266-Config";
	
	// Försök att ansluta. Om det misslyckas, starta portalen.
	// autoConnect returnerar 'true' om den lyckades ansluta,
	// och 'false' om den startade portalen och fick timeout.
	if (!wifiManager.autoConnect(apName.c_str()))
	{
	  Serial.println("Misslyckades att ansluta och fick timeout.");
	  Serial.println("Startar om...");
	  delay(3000);
	  // Starta om ESP:n för att försöka igen
	  ESP.restart();
	  delay(5000);
	}
	
	// Om vi kommer hit, är vi anslutna!
	Serial.println("");
	Serial.println("=========================================");
	Serial.println("WiFi ansluten!");
	Serial.print("IP-adress: ");
	Serial.println(WiFi.localIP());
	Serial.println("=========================================");
	
	// Släck lysdioden för att visa att vi är anslutna och klara.
	// (På NodeMCU tänds den istället, eftersom den är omvänd)
	digitalWrite(LED_BUILTIN, HIGH);
	server.begin();
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

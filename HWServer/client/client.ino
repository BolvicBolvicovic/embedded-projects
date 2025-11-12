#include "config.h"

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
	Serial.println("\nStart...");
	
	WiFiManager wifiManager;
	
	wifiManager.setConfigPortalTimeout(180);
	wifiManager.setAPCallback(configModeCallback);
	
	if (!wifiManager.autoConnect("ESP8266-Config"))
	{
	  Serial.println("Misslyckades att ansluta och fick timeout.");
	  Serial.println("Startar om...");
	  delay(3000);
	  ESP.restart();
	  delay(5000);
	}
	
	Serial.println("");
	Serial.println("=========================================");
	Serial.println("WiFi ansluten!");
	Serial.print("IP-adress: ");
	Serial.println(WiFi.localIP());
	Serial.println("=========================================");
	
	digitalWrite(LED_BUILTIN, HIGH);
}

bool	requested = false;

void
loop()
{
	if (!requested && WiFi.status() == WL_CONNECTED)
	{
		WiFiClient	client;
		HTTPClient	http;

		http.begin(client, server_root);

		PRINT("GET request to: ");
		PRINTLN(server_root);
		
		i32	resp_code = http.GET();
		
		if (resp_code > 0)
		{
			PRINT("HTTP Resp code: ");
			PRINTLN(resp_code);
			PRINTLN(http.getString());
		}
		else
		{
			PRINT("Error code: ");
			PRINTLN(resp_code);
		}

		http.end();

		requested = true;
	}

	yield();
}

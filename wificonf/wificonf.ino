/*
* WiFiManager Exempelkod för NodeMCU (ESP8266)
*
* 1. Laddar upp koden.
* 2. Öppna Seriell monitor (115200 baud).
* 3. Enheten startar. Om den inte har några sparade
* uppgifter startar den ett Wi-Fi-nätverk
* (Access Point) som heter "ESP8266-Config".
* 4. Anslut till "ESP8266-Config" med din telefon/dator.
* 5. En "captive portal" (inloggningssida) bör dyka upp
* automatiskt. Om inte, öppna en webbläsare och
* gå till http://192.168.4.1
* 6. Klicka på "Configure WiFi".
* 7. Välj ditt vanliga hemma-nätverk och ange lösenordet.
* 8. Klicka på "Save".
* 9. Enheten sparar, startar om och ansluter nu till
* ditt vanliga Wi-Fi.
*/
 
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
 
// Vi behöver en pinne för att blinka och visa att allt körs.
// På NodeMCU är LED_BUILTIN (GPIO 2) "omvänd" (LOW tänder den).
// På andra kort (som WEMOS D1) är den GPIO 2 (D4) och
// tänds med HIGH. Vi använder LED_BUILTIN för standard.
#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // Definiera om den inte finns
#endif
#define SERIAL_BAUDRATE	115200
 
// Funktion som anropas när konfigurationsportalen startar
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
	digitalWrite(LED_BUILTIN, LOW);
}
 
void
loop()
{
  // Din vanliga kod kommer här.
  // Denna körs bara efter att Wi-Fi är anslutet.
 
  // Exempel: Blinka långsamt för att visa att allt fungerar.
  digitalWrite(LED_BUILTIN, LOW); // Tänd
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH); // Släck
  delay(1000);
}

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
	Serial.println("\nStartar...");
	
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
}

bool	requested = false;

void
loop()
{
	if (!requested && WiFi.status() == WL_CONNECTED)
	{
		// Note: I am not using a smart pointer like Nihad does because I think it is important you understand what is happening here.
		// The *new* keyword ALLOCATES memory for the BearSSL::WiFiClientSecure object that we name client.
		// This memory is allocated on the HEAP (you should look up what this means online).
		// Memory allocated on the heap IS handled by the programmer and therefore, when you do not need the object anymore, you need to free that memory
		// so that it can be used by some other entity that would need that memory
		// (inside or outside your program, till exempel the RTOS, the WiFi thread...).
		// Note that when you allocate an object on the heap, what is returned is THE ADDRESS of that object.
		// An address is (almost) ALWAYS stored in a pointer which you write with a start "*" like this => ObjectType* ObjectName = new Object(Parameters);
		// You can also initialize it the way I write it below.
		BearSSL::WiFiClientSecure*	client(new BearSSL::WiFiClientSecure);
		HTTPClient	http;
		
		// Note: To use a method (function that is in the context of the object)
		// or anything else from an object that is at the address stored in a pointer (the pointer named "client" in our case),
		// you use an arrow "->" instead of a dot "." 
		client->setInsecure(); // If you called the method from the object itself and not the pointer, you would write: client.setInsecure();

		// Note: Here, to direcly access the object stored at the address of a pointer, you need to dereference that pointer.
		// It is does by adding a start "*" before the name of the pointer like so: *pointer
		// We do this here because the method .begin() requires us to pass the client itself and
		// neither its address nor a handle/reference (noted "&", you can look online for more info).
		// Note that we just pass the value here. It means we copy the object client onto the stack
		// so that the value of the object can be used by the method/function.
		http.begin(*client, server_path);

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

		requested = true;

		// Note: Now that we do not need our client anymore, as I mentioned earlier,
		// you need to free the memory that was used to store information about the client with the *delete* keyword
		delete client;
	}

	yield();
}

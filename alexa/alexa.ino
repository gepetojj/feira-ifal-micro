#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "pages.h"

#define LED_1_PIN 0

#define SSID "*******"
#define PASS "*******"

WebServer server(80);

unsigned int led_1_state = 0;

void handleRoot()
{
	String s = MAIN_page;
	server.send(200, "text/html", s);
}

void handleLed1On()
{
	led_1_state = 1;
	digitalWrite(LED_1_PIN, led_1_state);

	server.send(200, "text/plain", "OK");
}

void handleLed1Off()
{
	led_1_state = 0;
	digitalWrite(LED_1_PIN, led_1_state);

	server.send(200, "text/plain", "OK");
}

void handleLed1Blink()
{
	for (int x = 0; x < 2; x++)
	{
		digitalWrite(LED_1_PIN, HIGH);
		delay(300);
		digitalWrite(LED_1_PIN, LOW);
		delay(300);
	}

	led_1_state = 0;
	server.send(200, "text/plain", "OK");
}

void setup()
{
	Serial.begin(115200);

	pinMode(LED_1_PIN, OUTPUT);

	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PASS);

	Serial.print("Conectando ao WiFi...");
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		digitalWrite(LED_1_PIN, HIGH);
		delay(500);
		digitalWrite(LED_1_PIN, LOW);
		delay(500);

		Serial.print(".");
	}

	Serial.print("\nConectado em: ");
	Serial.println(SSID);
	Serial.print("Endereco IP: ");
	Serial.println(WiFi.localIP());

	server.on("/", handleRoot);
	server.on("/led/ligar", handleLed1On);
	server.on("/led/desligar", handleLed1Off);
	server.on("/led/blink", handleLed1Blink);

	server.begin();
}

void loop()
{
	// Printa o IP local se receber a mensagem "ip" no serial.
	if (Serial.available() != 0)
	{
		String input = Serial.readString();

		if (input == "ip")
		{
			Serial.print("Endereco IP: ");
			Serial.println(WiFi.localIP());
		}
	}

	server.handleClient();
	delay(1);
}
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

void setup(void)
{
	Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PASS);

	Serial.print("Conectando ao WiFi...");
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}

	Serial.print("\nConectado em: ");
	Serial.println(SSID);
	Serial.print("Endereco IP: ");
	Serial.println(WiFi.localIP());

	server.on("/", handleRoot);
	server.on("/led/ligar", handleLed1On);
	server.on("/led/desligar", handleLed1Off);

	server.begin();
}

void loop(void)
{
	server.handleClient();
	delay(1);
}
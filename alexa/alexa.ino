#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "pages.h"

#define LED_1_PIN 2
#define TEMP_1_PIN 35
#define BUZZER_1_PIN 5

#define SSID "*******"
#define PASS "*******"

WebServer server(80);

void handleRoot()
{
	String s = MAIN_page;
	server.send(200, "text/html", s);
}

void handleLed1On()
{
	digitalWrite(LED_1_PIN, HIGH);
	server.send(200, "text/plain", "Led ligado.");
}

void handleLed1Off()
{
	digitalWrite(LED_1_PIN, LOW);
	server.send(200, "text/plain", "Led desligado.");
}

void handleLed1Blink()
{
	for (int x = 0; x < 5; x++)
	{
		digitalWrite(LED_1_PIN, HIGH);
		delay(500);
		digitalWrite(LED_1_PIN, LOW);
		delay(500);
	}

	server.send(200, "text/plain", "OK.");
}

void handleTemp()
{
	int received = analogRead(TEMP_1_PIN);
	float voltage = received * (5000 / 1024.0);
	float temperature = voltage / 10;
	Serial.println(received);
	Serial.println(temperature);

	server.send(200, "text/plain", String(temperature));
}

void handleBuzzer()
{
	tone(BUZZER_1_PIN, 422, 2000);
	server.send(200, "text/plain", "OK.");
}

void setup()
{
	Serial.begin(115200);

	pinMode(LED_1_PIN, OUTPUT);
	pinMode(TEMP_1_PIN, INPUT);
	pinMode(BUZZER_1_PIN, OUTPUT);

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

	delay(2000);
	Serial.print("\nConectado em: ");
	Serial.println(SSID);
	Serial.print("Endereco IP: ");
	Serial.println(WiFi.localIP());

	server.on("/", handleRoot);
	server.on("/led/ligar", handleLed1On);
	server.on("/led/desligar", handleLed1Off);
	server.on("/led/blink", handleLed1Blink);
	server.on("/temp", handleTemp);
	server.on("/buzzer", handleBuzzer);

	server.begin();
}

void loop()
{
	// Printa o IP local se receber a mensagem "ip" no serial.
	if (Serial.available() != 0)
	{
		String input = Serial.readString();

		if (input == String("ip"))
		{
			Serial.print("Endereco IP: ");
			Serial.println(WiFi.localIP());
		}
	}

	server.handleClient();
	delay(1);
}
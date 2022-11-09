#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "pages.h"

#define AP_NAME "Alexa-no-ESP32"
#define LED_1_PIN 2
#define TEMP_1_PIN 35
#define BUZZER_1_PIN 5

String SSID = "";
wifi_mode_t WIFI_MODE = WIFI_MODE_AP;

WebServer server(80);
StaticJsonDocument<250> doc;

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

void handleSettings()
{
	String s = SETTINGS_page;
	server.send(200, "text/html", s);
}

void handleSettingsSee()
{
	doc.clear();
	doc["wifi_mode"] = WIFI_MODE == WIFI_MODE_AP ? "Access Point (AP)" : "Cliente (Conectado)";
	doc["connected_ssid"] = SSID.length() > 0 ? SSID : "Nenhum";

	String response = "";
	serializeJson(doc, response);

	server.send(200, "application/json", response);
}

void handleSettingsSet()
{
	if (SSID && WIFI_MODE != WIFI_MODE_AP)
	{
		server.send(500, "text/plain", "Já conectado ao WiFi.");
		return;
	}

	if (server.hasArg("plain") == false)
	{
	}

	doc.clear();
	String body = server.arg("plain");
	deserializeJson(doc, body);

	String ssid = doc["ssid"];
	String pass = doc["pass"];

	if (ssid == "")
	{
		server.send(400, "text/plain", "SSID nulo.");
		return;
	}

	const char *ssid_char = ssid.c_str();
	const char *pass_char = pass.c_str();

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid_char, pass_char);

	int attempts = 0;

	Serial.println("Conectando ao WiFi...");
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		attempts += 1;

		digitalWrite(LED_1_PIN, HIGH);
		delay(500);
		digitalWrite(LED_1_PIN, LOW);
		delay(500);
		Serial.print(".");

		if (attempts >= 10)
		{
			Serial.println("\nTempo para conexao expirou, voltando para modo AP.");
			tone(BUZZER_1_PIN, 1000, 1000);

			WiFi.softAP(AP_NAME);
			server.send(400, "text/plain", "Não foi possível conectar-se.");
			return;
		}
	}

	SSID = ssid;
	WIFI_MODE = WIFI_MODE_STA;

	Serial.print("\nConectado em: ");
	Serial.println(SSID);
	Serial.print("Endereco IP: ");
	Serial.println(WiFi.localIP());

	server.send(200, "text/plain", "OK.");
}

void setup()
{
	Serial.begin(115200);

	pinMode(LED_1_PIN, OUTPUT);
	pinMode(TEMP_1_PIN, INPUT);
	pinMode(BUZZER_1_PIN, OUTPUT);

	// Inicia o ESP no modo AP
	WiFi.softAP(AP_NAME);

	server.on("/", handleRoot);
	server.on("/led/ligar", handleLed1On);
	server.on("/led/desligar", handleLed1Off);
	server.on("/led/blink", handleLed1Blink);
	server.on("/temp", handleTemp);
	server.on("/buzzer", handleBuzzer);

	server.on("/settings", handleSettings);
	server.on("/settings/see", handleSettingsSee);
	server.on("/settings/set", HTTP_POST, handleSettingsSet);

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
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "pages.h"

#define SSID "******"
#define PASS "******"
#define ADC_1_PORT 36
#define ADC_2_PORT 39

float media;
float media2;
float tempC;
float tempC2;

WebServer server(80);
DynamicJsonDocument doc(70);

void handleRoot()
{
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void handleADC()
{

  int adcVal = analogRead(ADC_1_PORT);
  float milliVolt = adcVal * (5000.0 / 4096.0);
  float tempC = milliVolt / 10;

  for (int i = 0; i < 10; i++)
  {
    media = media + tempC;
    // delay(1000);
  }
  media = media / 10;

  // String adcValue = String(media);

  int adcVal2 = analogRead(ADC_2_PORT);
  float milliVolt2 = adcVal2 * (5000.0 / 4096.0);
  float tempC2 = milliVolt2 / 10;

  for (int i = 0; i < 10; i++)
  {
    media2 = media2 + tempC2;
    // delay(1000);
  }
  media2 = media2 / 10;

  // String adcValue2 = String(media2);

  /*
  Serial.print("Sensor 1: ");
  Serial.println(adcValue);
  Serial.print("Sensor 2: ");
  Serial.println(adcValue2);
  */

  // Define as keys 'sensor_1' e 'sensor_2' e atribui os valores dos sensores para elas
  doc["sensor_1"] = tempC;
  doc["sensor_1_mean"] = media;
  doc["sensor_2"] = tempC2;
  doc["sensor_2_mean"] = media2;

  // Cria uma string que receberá o JSON. Exemplo: { "sensor_1": 30.22, "sensor_2": 25.54 }
  String response = "";
  serializeJson(doc, response);

  // Devolve para o cliente a resposta com o JSON
  server.send(200, "application/json", response);
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);

  Serial.println("Connecting to ");
  Serial.print(SSID);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/readADC", handleADC);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
  delay(1);
}
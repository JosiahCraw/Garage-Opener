#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

#define RELAY0 3
#define RELAY1 1

const char* ssid = "TopShitNet";
const char* pass = "nosnakesallowed";

AsyncWebServer server(80);

IPAddress ip(192, 168, 1, 11);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  // put your setup code here, to run once:

  pinMode(RELAY0, OUTPUT);
  pinMode(RELAY1, OUTPUT);

  digitalWrite(RELAY0, LOW);
  digitalWrite(RELAY1, LOW);

  WiFi.config(ip, gateway, subnet, gateway);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  server.begin();

  server.on("/open", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(RELAY1, HIGH);
    delay(500);
    digitalWrite(RELAY1, LOW);
    request->send(200, "text/plain", "Opening...");
  });

  server.on("/on-extra", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(RELAY0, HIGH);
    request->send(200, "text/plain", "Second one on...");
  });

  server.on("/off-extra", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(RELAY0, LOW);
    request->send(200, "text/plain", "Second one off...");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    const char* message = "<html><iframe src='http://storage.googleapis.com/garageopener/v3/index.html' style='height: 100%; width: 100%;'></iframe></html>";
    request->send(200, "text/html", message);
  });
}

void loop() {

}

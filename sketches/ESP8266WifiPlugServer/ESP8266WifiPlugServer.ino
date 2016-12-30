/*
 * WIFI Plug with ESP8266 embedded
 * 
 * REFERENCES:
 *  https://github.com/scottjgibson/esp8266Switch
 *  https://github.com/windowfinn/esp8266-wifi-plug
 *  http://www.instructables.com/id/Turn-a-Cheap-WiFi-Plug-Into-an-OpenHAB-ESP8266-Swi/
 *  http://hackaday.com/2016/02/06/cheap-wifi-outlets-reflashed-found-to-use-esp8266/
 * 
 * TODO:
 *  add OTA,
 *  add usage monitoring (TOUT?)
 *  
 * REQUIREMENTS:
 *  need to have a credentials.h with SSID and password, or hardcode for vars below
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <credentials.h>

ESP8266WebServer server(80);

#define led 2
#define RELAY 15

void handleRoot() {
  digitalWrite(led, 0);
  server.send(200, "text/plain", "WIFI Plug #1");
  digitalWrite(led, 1);
}

void handleOff() {
  digitalWrite(led, 0);
  digitalWrite(RELAY, LOW);
  server.send(200, "text/plain", "ok");
  digitalWrite(led, 1);
}

void handleOn() {
  digitalWrite(led, 0);
  digitalWrite(RELAY, HIGH);
  server.send(200, "text/plain", "ok");
  digitalWrite(led, 1);
}

void handleNotFound() {
  digitalWrite(led, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
}

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}

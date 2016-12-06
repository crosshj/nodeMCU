#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

// to connect to wifi with password
#include <credentials.h>

ESP8266WebServer server(80);

SoftwareSerial softSerial(D3, D2); // RX, TX

const int led = LED_BUILTIN;
String command="";
String bufferCommand="";

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", command);
  digitalWrite(led, 0);
  Serial.println("Connected on root");
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  softSerial.begin(115200);
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

  server.begin();
  softSerial.println("WIFI READY");
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();

  if(softSerial.available()){
    delay(1000);
    digitalWrite(led, 1);
    bufferCommand = "";
    while(softSerial.available()){
      bufferCommand+=(char)softSerial.read();
    }
    command+=bufferCommand;
    digitalWrite(led, 0);
  }
}

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

#include <credentials.h>

ESP8266WebServer server(80);

SoftwareSerial softSerial(D1, D2); // RX, TX

const int led = LED_BUILTIN;
String command="A5, A4\n------\n";
String bufferCommand="";

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", command);
  digitalWrite(led, 0);
  Serial.println("Connected on root");
}

void handleNotFound(){
  digitalWrite(led, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
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

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
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

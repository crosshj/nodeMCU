#include <SoftwareSerial.h>

// RX Arduino pin 4 connects to ESP8266's TX pin
// TX Arduino pin 5 connects to ESP8266's RX pin
SoftwareSerial esp8266(4,5); 

int EN_RIGHT=9;
int EN_LEFT=10;

int counterRight = 0;
void doCountRight() {
  counterRight++;
}

int counterLeft = 0;
void doCountLeft() {
  counterLeft++;
}

void setup() {
  Serial.begin(115200);
  esp8266.begin(115200);

  delay(10000);
  attachInterrupt(0, doCountRight, RISING);
  attachInterrupt(1, doCountLeft, RISING);
  esp8266.write("LEFT, RIGHT\n---------\n");
}
 
void loop() {
  //TODO: PID for motor speed
  analogWrite(EN_RIGHT, 255);
  analogWrite(EN_LEFT, 255);

  delay(1000);
  esp8266.print(counterLeft);
  esp8266.print(", ");
  esp8266.println(counterRight);
}
 

#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(115200);
  esp8266.begin(115200); // your esp's baud rate might be different
  esp8266.write("[Arduino Boot]\n");
}
 
void loop()
{
  if(esp8266.available()){
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    }  
  }

  if(Serial.available()){
    delay(1000); 
    String command="";
    while(Serial.available()){
      command+=(char)Serial.read();
    }
    esp8266.println(command); // send the read character to the esp8266
  }
  delay(1000);
  esp8266.print(analogRead(5));
  esp8266.print(", ");
  esp8266.println(analogRead(4));
}
 

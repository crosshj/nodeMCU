#define LED_PIN 13
#define RELAY_PIN 12
#define BUTTON_GPIO 0
#define INPUT_PIN 14

//10 – MTDI  GPIO  GPIO12  Relay (HIGH to turn on)
//12 – MTCK GPIO  GPIO13  LED (LOW to turn on)

void setup(void) {   
  Serial.begin(115200);
  delay(5000); 
  Serial.println(""); 
  Serial.println("START"); 
  pinMode(LED_PIN, OUTPUT); 
} 

void loop(void) { 
  digitalWrite(LED_PIN, HIGH); 
  delay(1000); 
  digitalWrite(LED_PIN, LOW); 
  delay(1000);
  Serial.println("LED");
}

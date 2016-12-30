
#define LED_0 2
#define RELAY 15

void setup() {
  pinMode(LED_0, OUTPUT);
  pinMode(RELAY, OUTPUT);
}

void loop() {
  digitalWrite(LED_0, LOW); // ON
  digitalWrite(RELAY, HIGH);
  delay(1000);

  digitalWrite(LED_0, HIGH); // OFF
  digitalWrite(RELAY, LOW);
  delay(1000);
}

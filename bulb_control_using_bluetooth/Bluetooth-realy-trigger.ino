#define RELAY_PIN 7

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Relay OFF initially
  Serial.begin(9600);            // HC-05 default baud rate
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == '1') {
      digitalWrite(RELAY_PIN, HIGH);  // Turn ON relay (AC bulb ON)
    } else if (command == '0') {
      digitalWrite(RELAY_PIN, LOW);   // Turn OFF relay (AC bulb OFF)
    }
  }
}

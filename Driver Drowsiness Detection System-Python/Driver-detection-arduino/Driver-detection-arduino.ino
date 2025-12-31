// ============================================
// Arduino Relay Control via Serial (0 and 1)
// ============================================

const int RELAY_PIN = 7;

// ❗ Most relay modules are ACTIVE LOW.
// Meaning:
//    LOW  = Relay ON
//    HIGH = Relay OFF
// Change these if your relay behaves opposite.
const bool RELAY_ON  = LOW;
const bool RELAY_OFF = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  // Start with relay OFF
  digitalWrite(RELAY_PIN, RELAY_OFF);
}

void loop() {
  if (Serial.available()) {
    char incoming = Serial.read();

    if (incoming == '0') {
      // Trigger relay ON
      digitalWrite(RELAY_PIN, RELAY_ON);
      Serial.println("RELAY_ON");
    }

    else if (incoming == '1') {
      // Trigger relay OFF
      digitalWrite(RELAY_PIN, RELAY_OFF);
      Serial.println("RELAY_OFF");
    }
  }
}

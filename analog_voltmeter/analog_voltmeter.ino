// Pin used to read the analog voltage
const int readPin = A4;

// variable to store the measured value
int V2 = 0;

void setup() {
  // configure the analog pin and serial port
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the voltage level on the analog pin
  V2 = analogRead(readPin);
  Serial.println(V2);
  delay(500);
}

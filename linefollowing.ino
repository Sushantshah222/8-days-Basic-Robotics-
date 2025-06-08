// Motor Pins
#define ENA 10
#define ENB 11
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

// Line Sensor Pins
#define LEFT_SENSOR A0
#define RIGHT_SENSOR A1

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
}

void loop() {
  int leftSensor = digitalRead(LEFT_SENSOR);
  int rightSensor = digitalRead(RIGHT_SENSOR);

  if (leftSensor == LOW && rightSensor == LOW) {
    // Both sensors on black → Move forward
    forward();
  } else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left on black, right on white → Turn left
    turnLeft();
  } else if (leftSensor == HIGH && rightSensor == LOW) {
    // Right on black, left on white → Turn right
    turnRight();
  } else {
    // Lost line → Stop or search
    stopMotors();
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 150);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 0);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

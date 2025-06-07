#include <SoftwareSerial.h>

// Bluetooth serial pins
#define BT_RX 8
#define BT_TX 9

SoftwareSerial BTSerial(BT_RX, BT_TX); // RX, TX

// Motor control pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

void setup() {
  // Set motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Start serial communication with Bluetooth
  BTSerial.begin(9600);  // HC-05 default baud rate

  // Start serial communication with Serial Monitor
  Serial.begin(9600);
  Serial.println("Bluetooth Controlled Bot Ready");
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    Serial.print("Received Command: ");
    Serial.println(command);

    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMotors();
        break;
      default:
        Serial.println("Unknown command");
        break;
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Action: Moving Forward");
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Action: Moving Backward");
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Action: Turning Left");
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Action: Turning Right");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Action: Stopping");
}

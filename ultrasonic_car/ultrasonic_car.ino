

#define trigPin 6
#define echoPin 13

void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
 
}
  
 

void forward()
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  Serial.println("Forward");
}
void backward()
{
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
}
void right()     // Sharp right trun
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
}
void left()      //sharp left trun
{
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
}
void stops()
{

 digitalWrite(8,LOW);
  digitalWrite(9,LOW);
 digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  }






void loop() {
  float Time, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  Time = pulseIn(echoPin, HIGH);
  distance = (Time / 2) * 0.0344;
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  delay(500);

   if(distance >= 10)
   {
   forward();
   Serial.println("forward  ");
   }  
if(distance <= 5)
   {
   stops();
   Serial.println("Stops");
   delay(1000);
   
   backward();
   Serial.println("backward");
   delay(1000);
   right();
   Serial.println("right");
   }

   
  
}

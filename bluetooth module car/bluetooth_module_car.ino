
char value;

void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
  
 

}
void forward()
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
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
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  }




void loop() {
  if(Serial.available()>0){

    value = Serial.read();
    Serial.println(value);
    if(value=='F')
    {
      forward();
    
    }
    if(value=='B')
    {
      backward();
    
    }
    if(value=='R')
    {
      right();
    
    }
    if(value=='L')
    {
      left();
    
    }
    if(value=='S')
    {
      stops();
    
    }
    
  }
 

}

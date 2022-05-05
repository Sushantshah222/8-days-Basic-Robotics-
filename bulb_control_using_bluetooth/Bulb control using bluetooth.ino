char state; 
int LED = 13; 
int BULB = 8;
void setup() 
{   
   Serial.begin(9600); 
   pinMode(LED, OUTPUT); 
   pinMode(BULB, OUTPUT); 
   digitalWrite(BULB, LOW);
   Serial.println("Ready to connect\nDefualt password is 1234 or 000"); 
} 
void loop() 
{ 
   if (Serial.available())
   {
      state = Serial.read();
     
     if (state == 'G') 
     { 
        Serial.println(state);
        digitalWrite(LED, HIGH); 
        Serial.println("LED On"); 
     } 
     else if (state == 'R') 
     {
        Serial.println(state);
        digitalWrite(LED, LOW); 
        Serial.println("LED Off"); 
     }
  
     if (state == 'O') 
     { 
        Serial.println(state);
        digitalWrite(BULB, HIGH); 
        Serial.println("BULB On"); 
     } 
     else if (state == 'F') 
     {
        Serial.println(state);
        digitalWrite(BULB, LOW); 
        Serial.println("BULB Off"); 
     }
   }
}  

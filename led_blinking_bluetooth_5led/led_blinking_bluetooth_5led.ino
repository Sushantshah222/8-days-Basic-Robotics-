void setup() {

 pinMode(4, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);// put your setup code here, to run once:
 Serial.begin(9600);
 }

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available())
   {     
      char data= Serial.read(); // reading the data received from the bluetooth module

      if(data == 'a')  {   
      digitalWrite(4, HIGH);
      delay(100);
      digitalWrite(4, LOW);
      }
      if(data == 'b')  {   
      digitalWrite(7, HIGH);
      delay(100);
      digitalWrite(7, LOW);
      }
      if(data == 'c')  {   
      digitalWrite(8, HIGH);
      delay(100);
      digitalWrite(8, LOW);
      }
      if(data == 'd')  {   
      digitalWrite(12, HIGH);
      delay(100);
      digitalWrite(12, LOW);
      Serial.print("DDDDDDDD\n");
      }
      if(data == 'e')  {   
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);

      }
      
      if(data == 's')  {   
      
      Serial.print("Stop\n");

   }
     Serial.println(data);

}
delay(100);

}

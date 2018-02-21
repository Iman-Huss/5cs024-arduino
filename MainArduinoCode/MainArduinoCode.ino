
void setup() {
  Serial.begin(9600);
   pinMode(8, OUTPUT);
   
   pinMode(9, OUTPUT);
}

String stringOne;
boolean led1 = 0;
boolean led2 = 0;


void loop() {
   


  int count = 0;
      Serial.println("Test:");
     while(Serial.available() > 0)
  {
     char incomingByte= Serial.read();
     Serial.println("Test Byte: " + incomingByte);
     
     if(count==0)
     {
       if (incomingByte=='1')
        {
         led1 = 1;
        }
       else
        {
        led1 = 0;
        }
     }
       
     if(count==1)
     {
       if (incomingByte=='1')
         {
         led2 = 1;
         }
       else
         {
         led2 = 0;
         }
     }
     
     
     
     
     
     
     count++;
     
  }


digitalWrite(8,led1);
digitalWrite(9,led2);

delay(1000);

}

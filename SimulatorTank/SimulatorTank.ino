
const int buttonPin = 8;   
int ledIds[6];
int buttonState = 0;     
unsigned long previousMillis = 0;     
const long interval = 400; 
unsigned long previousMillis2 = 0;     
const long interval2 = 100;         
int currentLED = -1;


boolean valveClosed = false;
boolean flowStop = false;
boolean preOpening = false;
boolean flashYellowLED = false;
int ledState = 0;


boolean pressed = 0;
int flashLEDCount = 0;
boolean valveIsClosing = false;
  

void setup() {

  // set outputs and inputs
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);

 ledIds[0] = 7;
 ledIds[1] = 6;
 ledIds[2] = 5;
 ledIds[3] = 3;
    
 ledIds[4] = 2;
 digitalWrite(13, HIGH);
}



void loop()
{
if (valveIsClosing)
  {
  flashLED(false);
  }
else
  {
  
  if (!valveClosed)
  {  
    buttonState = digitalRead(9);
    if (buttonState == HIGH) {   
      if (!pressed)
        {
        if (flowStop==true)
          {
          preOpening = false;
          valveIsClosing = true;
          flashYellowLED = false;
          }
         else
          {
          flashYellowLED = true;
          }
        }
    pressed = true;
     }
     else
       {
       pressed = false;
       }

  if (!flowStop)
      {
       if (flashYellowLED)
         {
         flashLED(true);
         }
    
       unsigned long currentMillis = millis();
       if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (currentLED!=-1)
          {
          digitalWrite(ledIds[currentLED], LOW);
          }
          digitalWrite(ledIds[currentLED+1], HIGH);
          currentLED++;
        if (currentLED==5)
          {
          currentLED=-1; 
          }
      }
    }
 else
    {
    if (!preOpening)
      {
       finishFlow();
      }
    }
   }
   else  
    {
    buttonState = digitalRead(8);
    if (buttonState == HIGH) {  
     preValveUp();
     preOpening = true;
     valveClosed = false;
     currentLED = -1;
     }
   }
  }
}


void flashLED(boolean closingValue)
{
 unsigned long currentMillis2 = millis();
 if (currentMillis2 - previousMillis2 >= interval2) {
      previousMillis2 = currentMillis2;
  
      if (ledState==1)
       {
       digitalWrite(10, LOW);
       ledState = 0;
       }
      else
      {
      digitalWrite(10, HIGH);
      ledState =1;
      }
     
     flashLEDCount++;

     if (flashLEDCount==30)
     {
      if (closingValue)
       {
       flowStop = true;
       digitalWrite(4, HIGH);
       digitalWrite(13, LOW);
       digitalWrite(10, LOW);
       ledState = 0;
       flashLEDCount = 0;
       }
      else
       {
       flowStop = false;
       digitalWrite(4, LOW);
       digitalWrite(13, HIGH);
       digitalWrite(10, LOW);
       ledState = 0;
       flashLEDCount = 0;
       valveIsClosing = false;
      }
    }
 }
}


void finishFlow()
   {
    if (currentLED==2)
       {
       digitalWrite(ledIds[currentLED], LOW); 
       afterValveDown();
       preValveDown(false);
       valveClosed=true;
       } 
   
   if (currentLED==3)
       {
       digitalWrite(ledIds[currentLED], LOW);
       digitalWrite(ledIds[4], HIGH);
       delay(interval);
       digitalWrite(ledIds[4], LOW);
       preValveDown(false);
       valveClosed=true;
       }

   if (currentLED==0)
      {
      preValveDown(false);
      valveClosed=true;
      }

   if (currentLED==4)
     {
     digitalWrite(ledIds[4], LOW);
     preValveDown(false);
     valveClosed=true;
     }


   if (currentLED==1)
     {
     digitalWrite(ledIds[1], LOW);
     delay(interval);
     digitalWrite(ledIds[2], HIGH);
     delay(interval);
     digitalWrite(ledIds[0], HIGH);
     delay(interval);
     digitalWrite(ledIds[0], LOW);
     delay(interval);
     digitalWrite(ledIds[1], HIGH);
     valveClosed=true;
    }

}



void preValveUp()
{
     digitalWrite(ledIds[2], LOW);
     digitalWrite(ledIds[1], HIGH);
     digitalWrite(ledIds[0], HIGH);
     delay(1000);
     digitalWrite(ledIds[1], LOW);
     delay(1000);
     digitalWrite(ledIds[0], LOW);
}




void afterValveDown()
{
   digitalWrite(ledIds[3], HIGH);
     delay(interval);
     digitalWrite(ledIds[3], LOW);
     delay(interval);
     digitalWrite(ledIds[4], HIGH);
     delay(interval);
     digitalWrite(ledIds[4], LOW);
     delay(interval);
}




void preValveDown(boolean flow)
{

 
     digitalWrite(ledIds[0], HIGH);
     delay(interval);
     digitalWrite(ledIds[0], LOW);
     delay(interval);
     digitalWrite(ledIds[1], HIGH);
     delay(interval);
     digitalWrite(ledIds[1], LOW);
     delay(interval);
     digitalWrite(ledIds[2], HIGH);
     delay(interval);

if(flow)
{
    digitalWrite(ledIds[2], LOW);
    delay(interval);
    
}
else
{
  
     digitalWrite(ledIds[0], HIGH);
     delay(interval);
     digitalWrite(ledIds[0], LOW);
     delay(interval);
     digitalWrite(ledIds[1], HIGH);
     delay(interval);
}
}



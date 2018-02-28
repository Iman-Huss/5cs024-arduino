
const int buttonPin = 8;   
boolean fullTank  = false;
int tankLevel = 0;
int ledIds[6];
int buttonState = 0;     
int ledState = LOW;     
unsigned long previousMillis = 0;     
const long interval = 200;     
boolean tankFull = false;
  

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);

  ledIds[0] = 2;
   ledIds[1] = 3;
    ledIds[2] = 4;
     ledIds[3] = 5;
      ledIds[4] = 6;
       ledIds[5] = 7;
}



void loop() {
  unsigned long currentMillis = millis();
  if (tankFull)
    {
    buttonState = digitalRead(9);
    if (buttonState == HIGH) {
     emptyTank();
     } 
    else
     {
     if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
       if (ledState == LOW) {
          ledState = HIGH;
        } else {
           ledState = LOW;
          }
     digitalWrite(7, ledState);
     }
    }
   }
  else
  {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
  fillTank();
    if (!fullTank)
      {
      delay(1000);}
      } 
    }
 }


void fillTank()
{
tankLevel++;
lightLeds();
}

void lightLeds()
{
digitalWrite(ledIds[tankLevel+1], HIGH);

for(int i = 0;i!=6;i++)
{
  if (i>=tankLevel)
  {
   digitalWrite(ledIds[i], LOW);
  }
  else
  {
 digitalWrite(ledIds[i], HIGH);
  }
}
 if (tankLevel==6)  
  {
  tankFull = true;
  }
}


void emptyTank()
{
for(int i = 6;i!=-1;i--)
   {
  digitalWrite(ledIds[i-1], LOW);
  delay(1000);
 }
tankFull = false;
tankLevel = 0;
}


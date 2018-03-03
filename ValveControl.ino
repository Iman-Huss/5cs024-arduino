#include <SoftwareSerial.h>
#include <Stepper.h>

#define DEBUG true

//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 8   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION -2 * 64  //2048 

SoftwareSerial ESP8266(10, 11);

String wifiNetwork = "VM563367-2G"; // Garder les guillements
String Password = "sckmdzzu"; // Garder les guillements

boolean valveMoving = false;

int redPin = 13;
int greenPin = 12;
int amberPin = 9;

Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 2, 4, 3, 5);

int  Steps2Take;

/****************************************************************/
/*                             INIT                             */
/****************************************************************/
void setup()
{  
  pinMode(amberPin,OUTPUT);
  digitalWrite(amberPin,LOW);
  
  pinMode(greenPin,OUTPUT);
  digitalWrite(greenPin,LOW);

  pinMode(redPin,OUTPUT);
  digitalWrite(redPin,LOW);
  
  Serial.begin(9600);
  
  ESP8266.begin(115200);
  sendToESP8266("AT+CIOBAUD=9600");
  receiveFromESP8266(4000);

  ESP8266.begin(9600);  
  InitESP8266();
  ConnectToWebsite();

}



/****************************************************************/
/*                            Loop                              */
/****************************************************************/
void loop()
{
  
//   while(ESP8266.available())
//   {    
//     Serial.println(ESP8266.readString());
//   }  

  if(ESP8266.available()) // check if the esp is sending a message 
  {
    if(ESP8266.find("+IPD,"))
    {
      delay(500); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = ESP8266.read()-48; // subtract 48 because the read() function returns the ASCII decimal value
            
      ESP8266.find("pin="); // advance cursor to "pin="
      Serial.println("new client"); 
      int pinNumber = (ESP8266.read()-48); // get first number i.e.
      Serial.print("new pinNumber : "); 
      Serial.println(pinNumber, DEC);
      
      if(pinNumber == 1)
      {      
        digitalWrite(amberPin,HIGH);
        digitalWrite(redPin,LOW);
        digitalWrite(greenPin,LOW);
        valveMoving = true;
        openValve();
      }
      
      if(pinNumber == 2)
      {
        digitalWrite(amberPin,HIGH);
        digitalWrite(redPin,LOW);
        digitalWrite(greenPin,LOW);
        valveMoving = true;
        closeValve();
      }     
    }
  }  
}

/* Function to initialise ESP8266 */
void InitESP8266()
{  
  Serial.println("********************** INITIALISATION *********************"); 
  sendToESP8266("AT");
  receiveFromESP8266(2000);
  Serial.println("***********************************************************");
  sendToESP8266("AT+CWMODE=3"); //Wifi mode - softAP + station mode
  receiveFromESP8266(5000);
  Serial.println("***********************************************************");
  sendToESP8266("AT+CWJAP=\""+ wifiNetwork + "\",\"" + Password +"\""); //connect to wifi network
  receiveFromESP8266(10000);
    
  Serial.println("***********************************************************");
  sendToESP8266("AT+CIFSR"); //Display the IPs adress (client + server)
  receiveFromESP8266(5000);
  Serial.println("***********************************************************");
  sendToESP8266("AT+CIPMUX=1");  //set multiple connections 
  receiveFromESP8266(5000);
  Serial.println("***********************************************************"); 
  /* configures the module as the server. It will then enable external clients to connect to the module.
  The port number is set for listening.*/
  sendToESP8266("AT+CIPSERVER=1,80");
  receiveFromESP8266(5000);
  Serial.println("******************* INITIALISATION DONE *******************");
}


/* Function to connect to the server */
void ConnectToWebsite()
{
  Serial.println(".................. CONNECTION TO SERVER ....................");
  sendToESP8266("AT+CIPSTART=1,\"TCP\",\"mi-linux.wlv.ac.uk\",80"); //connect to website
  receiveFromESP8266(10000);
  Serial.println("***************** CONNECTION TO SERVER: OK ****************");
  sendToESP8266("AT+CIPSEND=1,114"); //send message to connection 1, 114 bytes
  receiveFromESP8266(5000);

  String httpreq = "GET /~1429422/receiver.php?lecturers=7&students=342 HTTP/1.1";
  // Make a HTTP request:
  sendToESP8266(httpreq);
  receiveFromESP8266(10000);
  sendToESP8266("Host: mi-linux.wlv.ac.uk");
  sendToESP8266("Connection: close");
  sendToESP8266("");   
  receiveFromESP8266(5000);
  Serial.println("\r\n");
}

/* Function that send commands to the ESP8266 */
void sendToESP8266(String commande)
{  
  ESP8266.println(commande);
}

/*Function that read and display messages sent by ESP8266 (with timeout)*/
void receiveFromESP8266(const int timeout)
{
  String reponse = "";
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(ESP8266.available())
    {
      char c = ESP8266.read();
      reponse+=c;
    }
  }
  Serial.print(reponse);   
}


void openValve(){

  for (int i = 0; i<8; i++){
      digitalWrite(amberPin, LOW);
    Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
    small_stepper.setSpeed(1000);   
    small_stepper.step(Steps2Take);
    //delay(10);
    digitalWrite(amberPin, HIGH);
    Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CW 1 turn  
    small_stepper.setSpeed(1000);  // 700 a good max speed??
    small_stepper.step(Steps2Take);
    //delay(10);
  }
  
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,HIGH);
  digitalWrite(amberPin, LOW);
}


void closeValve(){
  for (int i = 0; i<8; i++){
      digitalWrite(amberPin, LOW);
    Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CCW 1 turn
    small_stepper.setSpeed(1000);   
    small_stepper.step(Steps2Take);
    //delay(10);
    digitalWrite(amberPin, HIGH);
    Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CCW 1 turn  
    small_stepper.setSpeed(1000);  // 700 a good max speed??
    small_stepper.step(Steps2Take);
    //delay(10);
  }

  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,LOW);
  digitalWrite(amberPin, LOW);
}


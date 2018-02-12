#include <SoftwareSerial.h>

SoftwareSerial ESP8266(10, 11);

String wifiNetwork = "LenovoP2"; // Garder les guillements
String Password = "password"; // Garder les guillements

/****************************************************************/
/*                             INIT                             */
/****************************************************************/
void setup()
{
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
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
   while(ESP8266.available())
   {    
     Serial.println(ESP8266.readString());
   }  
   
}

/* Function to initialise ESP8266 */
void InitESP8266()
{  
  Serial.println("***********************************************************");  
  Serial.println("********************** INITIALISATION *********************");
  Serial.println("***********************************************************");  
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
  receiveFromESP8266(1000);
  Serial.println("***********************************************************");
  sendToESP8266("AT+CIPMUX=1");  //set multiple connections 
  receiveFromESP8266(1000);
  Serial.println("***********************************************************"); 
  /* configures the module as the server. It will then enable external clients to connect to the module.
  The port number is set for listening.*/
  sendToESP8266("AT+CIPSERVER=1,80");
  receiveFromESP8266(1000);
  Serial.println("***********************************************************");
  Serial.println("******************* INITIALISATION DONE *******************");
  Serial.println("***********************************************************");  
}

/* Function to connect to the server */
void ConnectToWebsite()
{
  Serial.println(".................. CONNECTION TO SERVER ....................");
  sendToESP8266("AT+CIPSTART=1,\"TCP\",\"mi-linux.wlv.ac.uk\",80"); //connect to website
  receiveFromESP8266(10000);
  Serial.println("***************** CONNECTION TO SERVER: OK ****************");
  sendToESP8266("AT+CIPSEND=1,114"); //send message to connection 1, 114 bytes
  receiveFromESP8266(2000);

  String httpreq = "GET /~1429422/receiver.php?lecturers=7&students=342 HTTP/1.1";
  // Make a HTTP request:
  sendToESP8266(httpreq);
  receiveFromESP8266(10000);
  sendToESP8266("Host: mi-linux.wlv.ac.uk");
  sendToESP8266("Connection: keep-alive");
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



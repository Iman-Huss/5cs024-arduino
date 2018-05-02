// imports

#include <SoftwareSerial.h>
#include <Stepper.h>
#include <LiquidCrystal.h>
#include <avr/pgmspace.h> // import memory

boolean inTestMode = false;
boolean valveClosed = false;
boolean valveError = false;
boolean wiFiSetDone = false;
boolean doSendData = true;
boolean liquidTrigger = false;
boolean testMode = false;

// const vars for valve states

int const STATE_VALVE_OPEN = 1000;
int const STATE_VALVE_CLOSED = 2000;
int const STATE_VALVE_HALF = -1000;
const String valveID = "1837"; // valve ID
String ipNumber;


int currentValveState = STATE_VALVE_HALF;
int ledState = 0;

// motor defines
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )
#define STEPS_PER_MOTOR_REVOLUTION 32
//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION -2 * 64  //2048 

 
SoftwareSerial ESP8266(11, 12); // RX, TX


// RGB Pins
const int redPin = 6;
const int greenPin = 10; // pin 10 swapped with pin 13 ( SoftwareSerial ) becasuse pin 13 was not PWM 
const int bluePin = 9;

// sensor pins
const int openSensorPin = 8;
const int closeSensorPin = 7;
const int liquidSesnorPin = 13;


// Initialize Stepper Motor
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 2, 3, 4, 5);

// initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(A0, A1, A5, A4, A3, A2);


/****************************************************************/
/*                       INITIALISATION                         */
/****************************************************************/

void setup()
{  
  // Analog Pin to connect with LCD
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

   lcd.clear();
//   set up the LCD's number of columns and rows:
   lcd.begin(16, 2);

  pinMode(bluePin,OUTPUT);  
  pinMode(greenPin,OUTPUT);
  pinMode(redPin,OUTPUT);
  
  pinMode(openSensorPin,INPUT);
  pinMode(closeSensorPin,INPUT);
  pinMode(liquidSesnorPin,INPUT);
  

 // Initialise the serial com
  Serial.begin(9600);  

  small_stepper.setSpeed(600); // sets speed of motor  
  
  sendLCD(F("STARTING UP...."),"1");
  closeValve(); // closes valve
  setupWiFi(); // setup wifi
  currentValveState = STATE_VALVE_CLOSED; // set state to closed
  sendLCD(F("VALVE CLOSED...."),"0"); 
  sendDataToWebsite(F("START"),"YES","NO","NO");   // send message to website saying its closed        
}

 // function  to setup wifi system
void setupWiFi()
{
  sendLCD(F("SETTING WIFI UP"),"1"); 

  setColor(0, 0, 255); // turns on blue LED to indicate initialisation of system. 
  
  if (!inTestMode) { // added so quick testing can take place......
   ESP8266.begin(115200);
   sendToESP8266("AT+CIOBAUD=9600");
   receiveFromESP8266(1000);
   ESP8266.begin(9600);  
   connectWifi();
   wiFiSetDone = true;
  }
   // flashes RGB LED indicating system is ready for internet connection
  setColor(0, 0, 0); 
  delay(150);
  setColor(0, 0, 255);
  delay(150); 
  setColor(0, 0, 0);
  delay(150); 
  setColor(0, 0, 255);
  delay(150); 
  setColor(0, 0, 0);
  delay(150); 
  setColor(255, 0, 0); // sets the led to red  indicating valve closed
}

void loop()
{
 
  // ------------------------------- Startup check gets the state of the valve ------------------------------ //
       

 
mainLoop(); // runs the main loop     
 
}

void mainLoop()
{  
if(digitalRead(liquidSesnorPin)==HIGH) { // checks to see if liquid in chamber
   liquidTrigger = true; // liquidTrigger used so only one message sent to server
  }
  else {
      if(liquidTrigger) {
          if(!testMode) {
               if(!valveClosed) {  
                  sendDataToWebsite(F("CLOSED"),"NO","NO","NO");   // send message to website saying its closed no liquid
               } 
          }
      liquidTrigger = false;
      }
  }

if(inTestMode) {// open and close Test
  setColor(255, 0, 0);  // red
  delay(500);
  setColor(0, 255, 0);  // green
  delay(500);
  setColor(0, 0, 255);  // blue
  delay(500); 
  openValve();
  delay(2000);
  closeValve();
  inTestMode = false;
}

  if(ESP8266.available()) {// check if the esp is sending a message 
  
    if(ESP8266.find("+IPD,")) { // If network data received from a single connection
      delay(500); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = ESP8266.read()-48; // subtract 48 because the read() function returns the ASCII decimal value
            
       ESP8266.find("pin="); // advance cursor to "pin="
    //  Serial.println("new client"); // Display info serial console
       int pinNumber = (ESP8266.read()-48); // get first number
    //  Serial.print("new pinNumber : "); // Display info serial console
  //    Serial.println(pinNumber, DEC);

      // If order 1 received: Open the valve
      if(pinNumber == 1) {
        valveError = false;
        openValve();
      }

      // If order 2 received: Close the valve
      if(pinNumber == 2) {
        valveError = false;
        closeValve();
      }     

      // If order 3 received: send data to the server used for testing data
      if(pinNumber == 3) {      
      //   sendDataToWebsite("123","NA","NO","NO");
      }  

      if(pinNumber == 4) {// valve test 
       testValve();
      }     
      if(pinNumber == 5) {// system reset 
      software_Reset();
      }

      if(pinNumber == 6) {// system reset 
        valveError = false;
      }           
    }
  }   
}

String testValve()
{
 
  testMode = true;
  setColor(255, 0, 0);  // red
  delay(500);
  setColor(0, 255, 0);  // green
  delay(500);
  setColor(0, 0, 255);  // blue
  delay(500); 
  if(valveClosed) {
      openValve();
      delay(2000);
      closeValve();   
  }
  else {
     closeValve();  
     delay(2000); 
     openValve();
  }

 delay(5000); //  delay before it sends pass
 
 if(!valveError) {
  sendDataToWebsite("PASS","NA","NO","NO");
 }
 else {
   sendDataToWebsite("FAIL","NA","YES","NO");
   valveError = false;
 }

 testMode = false;
 
}

/* Function to initialise the ESP8266 */
void connectWifi() 
{  

  //String wifiNetwork = "MOHAESP"; // Garder les guillemets
  //String Password = "password"; // Garder les guillemets

  String wifiNetwork = "wolfradiolan"; // Garder les guillemets
  String Password = "12345678"; // Garder les guillemets

  //const String wifiNetwork = "lap_hotspot"; // Garder les guillemets
  //const String Password = "12345678"; // Garder les guillemets
  
 
  sendToESP8266("AT");
  receiveFromESP8266(100);
  sendToESP8266("AT+CWMODE=3"); //Wifi mode - softAP + station mode
  receiveFromESP8266(100);
  ESP8266.println("AT+CIPSTO=7200"); // set timeout for server and TCP requests
  receiveFromESP8266(100);

  sendToESP8266("AT+CWJAP=\""+ wifiNetwork + "\",\"" + Password +"\""); //connect to wifi network
  receiveFromESP8266(16000);

  sendToESP8266("AT+CIFSR"); //Display the IPs adress (client + server)
  receiveFromESP8266(5000,true);
  sendToESP8266("AT+CIPMUX=1");  //set multiple connections 
  receiveFromESP8266(100);
  
  /* configures the module as the server. It will then enable external clients to connect to the module.
  The port number is set for listening.*/
  sendToESP8266("AT+CIPSERVER=1,80");
  receiveFromESP8266(100);

}


void software_Reset() // Restarts program via software can be used to reset from website
{
asm volatile ("  jmp 0");  
}  


// function to display output to LCD not used Yet
void sendLCD(String message, String line)
{
   
  if (line.equals("0")) {
    
     lcd.setCursor(0, 0); // displays on top line
     //lcd.clear();
     lcd.print(message);
  }

   if (line.equals("1")) {
   
     lcd.setCursor(0, 1); // displays on bottom line
     //lcd.clear();
     lcd.print(message);
   }
  
}




/* Function to connect to the uni server */


// checks sensor readings
String isLiquidInChamber()
{
  if (digitalRead(liquidSesnorPin)==HIGH){
   return "Full"; 
  }  
  else {
     return "Empty"; 
  }
}


// sends a post request so that data can be sent to PHP Script then to website
void sendDataToWebsite(String dataSent, String chamberStatus, String fault, String emer)
{
  if(doSendData) {
  String data = "id=" + valveID + "&v=" + dataSent + "&c=" + chamberStatus + "&f=" + fault + "&e=" + emer ;  
  httppost (data,F("mi-linux.wlv.ac.uk") , F("/~1606512/NewWebUi/valve_con.php") ); 
  }
}


// gets the length of the request string.
int createRequestL(String data, String server, String uri)
{
int postRequest = 
("POST " + uri + " HTTP/1.0\r\n" +
"Host: " + server + "\r\n" +
"Connection: keep-alive" + "\r\n" +
"Accept: *" + "/" + "*\r\n").length();

String dataL;
dataL = data.length();

int postRequest2 = ("Content-Length: " + dataL + "\r\n").length();
int postRequest3 = ("Content-Type: application/x-www-form-urlencoded\r\n\r\n" +  data).length();
return postRequest + postRequest2+ postRequest3;

}

int sendTrys = 0;
// creates request string
void createRequest(String data, String server, String uri)
{
String dataL;
dataL = data.length();
ESP8266.print("POST " + uri + " HTTP/1.0\r\n" +
"Host: " + server + "\r\n" +
"Connection: keep-alive" + "\r\n"); //+
//"Accept: *" + "/" + "*\r\n");
delay(200); //1000 // 100
ESP8266.print("Content-Length: " + dataL + "\r\n");
delay(200); //1000 // 100
ESP8266.print("Content-Type: application/x-www-form-urlencoded\r\n\r\n" +  data);
delay(200); //1000 // 100
}

// creates http request post.
void httppost (String data, String server, String uri) { 
  Serial.println("HTTP_POST");  
  
  sendLCD(F("DATA SEND...."),"0");
  boolean sent = false; 

  if(!wiFiSetDone) {
     setupWiFi();    
  }
  
  ESP8266.println("AT+CIPSTART=1,\"TCP\",\"" + server + "\",80");//start a TCP connection.  

  delay(100);
  
  if(ESP8266.find("OK")) {
   receiveFromESP8266(100); // 1000 // 100
   sent = true;


   int len = createRequestL(data,server,uri); // calulates the length of the request string.

   String sendCmd = "AT+CIPSEND=1,";//determine the number of caracters to be sent.
   ESP8266.print(sendCmd);
   ESP8266.println(len);

   delay(100); // 1000 //200
   createRequest(data,server,uri); // creates and sends the request string.
  // delay(5000); //5000


   String responce = receiveFromESP8266(5000);

   
    // close the connection
   ESP8266.println("AT+CIPCLOSE=1");
   receiveFromESP8266(1000);

  if(responce!="SEND OK") { // retry again
    sendTrys++;
    sent==false;
    if(sendTrys==5) {
      sent==true; // stop after 5 goes
      sendTrys = 0;
    }
    
  }

    
 }

if(sent==false) { // if not sent reset wifi and try again.
   // Serial.println("trying again");  
    sendLCD(F("DATA SENT ERROR..."),"0");
    delay(500); // 1000
    httppost(data,server,uri);
  }
  else
  {
     sendLCD(F("DATA SENT OK..."),"0");
  }
}

/* Function that send commands to the ESP8266 */
void sendToESP8266(String commande)
{  
  ESP8266.println(commande);
}


String receiveFromESP8266(const int timeout) // standard method with different inputs
  {
  return receiveFromESP8266(timeout, false);
  }


/*Function that read and display messages sent by ESP8266 (with timeout)*/
String receiveFromESP8266(const int timeout, boolean LCD)
{
  String reponse = "";
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(ESP8266.available()) {
      char c = ESP8266.read();
      reponse+=c;
    }
  }

  if(!LCD) {
     Serial.print(reponse);  
  } 
  else {
  ipNumber = extractIP(reponse);
  sendLCD(ipNumber,"1"); 
  }

  return reponse;
}


// gets the ip number from the responce string
String extractIP(String reponse)
{
  ipNumber = "";
  int startIndex = reponse.indexOf("+CIFSR:STAIP,"); // getes the IP number string and splits the text to the correct string.
  startIndex = startIndex + 14;
  ipNumber = reponse.substring(startIndex);
  int endIndex = reponse.indexOf("+CIFSR:STAMAC");
  endIndex = endIndex;
  ipNumber = reponse.substring(startIndex, (endIndex-3));
  return ipNumber;
}



// A function to check if the valve has hit the limit switches, if not the stepper is moved forward once, if  limit swicth reached stepper is stopped.
boolean loopSteps(int numberOfSteps,boolean opening)
{
  int flashCount = 0;
  setColor(0, 0, 0);


/// ------------------------------------------ VALVE TIMER CODE IF IT TAKES TOO LONG TO OPEN OR CLOSE SYSTEM WILL SEND AN ERROR

 
  unsigned long startMillis = millis();     
  for(int i  = 0;i>numberOfSteps;i++) {// loops thro steps  
   
    // function to time openening and closing of valve if longer them 16 seconds there is an error
    if ((millis() - startMillis) > 16000) {
    valveError = true;    
    sendDataToWebsite(F("ERROR"),"NA","YES","NO");
    break;
    }
      if (opening) {
           
         if(digitalRead(openSensorPin)) { // checks open limit switch
                 
           if(flashCount==50){ // flashes LED
          
          if (ledState==0) {
          
            ledState = 1;            
          }
          else {        
            ledState = 0;
          }
          flashCount=0;
          }
         
          if (ledState==0) {
          setColor(190, 10, 0); // Turn the Led Amber
          }
          else {
             setColor(0, 0, 0);
          }
          flashCount++;
          small_stepper.step(1); // move motor
          }
         else { 
           currentValveState = STATE_VALVE_OPEN;
           return false;
          }
       }
       else {  
        if(digitalRead(closeSensorPin)){ // checks closed limit switch
         
          if(flashCount==50) {
          
          if (ledState==0){
            ledState = 1;
          }
          else {
            ledState = 0;
          }
          flashCount=0;
          }
         
          if (ledState==0) {
          setColor(190, 10, 0); // Turn the Led Amber
          }
          else {
            setColor(0, 0, 0);
          }
         flashCount++;
         small_stepper.step(-1); // moves motor
         }
        else {
          currentValveState = STATE_VALVE_CLOSED;
          return false;
        }
    }
  }
}



// Function to open the valve
void openValve(){

 sendLCD(F("OPENING VALVE...."),"0");
  // Serial.print("Error ");  
  // Serial.println(valveError);  
  if(!valveError)
  {
  for (int i = 0; i<8; i++){  
    if(valveError){break;}
    setColor(0, 0, 0); // Turn Off the Led
    if(!loopSteps(STEPS_PER_OUTPUT_REVOLUTION, true)){break;} // runs funtion to move stepper motor step bu step so that limit switch can be used - saves over run
  }  
    if(!valveError) {
       setColor(0, 255, 0); // Turn the Led Green
       valveClosed = false;
       sendLCD(F("VALVE OPEN...."),"0");
        if(!testMode) {
           sendDataToWebsite("OPEN","NO","NO","NO");
        }
    }
  }
}

// Function to close the valve
void closeValve(){
  
  sendLCD(F("CLOSING VALVE...."),"0");
  if(!valveError)
  {
  for (int i = 0; i<8; i++){
     if(valveError){break;}
    setColor(0, 0, 0); // Turn Off the Led  
    if(!loopSteps(STEPS_PER_OUTPUT_REVOLUTION, false)){break;} // runs funtion to move stepper motor step bu step so that limit switch can be used - saves over run
  } 
  if(!valveError) {
  setColor(255, 0, 0); // Led turn red
  valveClosed = true;

  if(wiFiSetDone) {// open send if wifi is setup
      sendLCD(F("VALVE CLOSED...."),"0"); 
       if(!testMode) {
          sendDataToWebsite("CLOSED","YES","NO","NO");
       }
   }
  }
 }
}


// Function to set the RGB Led color
void setColor(int red, int green, int blue)
{
  // used if RGB LED IS COMMON ANODE
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

// function to check open and closed sensors to get current state of valve (Open or Closed)
int checkValveState()
{
  boolean openCheck = false;
  
  if (!digitalRead(openSensorPin)){
   return STATE_VALVE_OPEN;
  }
  
  if (!digitalRead(closeSensorPin)){
    return STATE_VALVE_CLOSED;
  }
  else{
    return STATE_VALVE_HALF;
  }
}



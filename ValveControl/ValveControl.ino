#include <SoftwareSerial.h>
#include <Stepper.h>
#include <LiquidCrystal.h>

#define DEBUG true

boolean testWithoutWiFi = false; // added for quick testing without wifi
boolean inTestMode = false;
boolean testSend = true;

// const vars for valve states

int const STATE_VALVE_OPEN = 1000;
int const STATE_VALVE_CLOSED = 2000;
int const STATE_VALVE_HALF = -1000;

boolean wiFiSetDone = false;
unsigned long timeTestStart;

int currentValveState = STATE_VALVE_HALF;

int flashEveryAmount = 50;
int ledState = 0;

//---( Number of steps per revolution of INTERNAL motor in 4-step mode ) NOT USED
#define STEPS_PER_MOTOR_REVOLUTION 32
int speed = 950;
//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION -2 * 64  //2048 

 
SoftwareSerial ESP8266(11, 12); // RX, TX

//String wifiNetwork = "MOHAESP"; // Garder les guillemets
//String Password = "password"; // Garder les guillemets

String wifiNetwork = "wolfradiolan"; // Garder les guillemets
String Password = "12345678"; // Garder les guillemets

//String wifiNetwork = "lap_hotspot"; // Garder les guillemets
//String Password = "12345678"; // Garder les guillemets

boolean valveMoving = false;

boolean startup = true; 
boolean firstLoop = true;

//#define COMMON_ANODE

int redPin = 6;
int greenPin = 10; // pin 10 swapped with pin 13 ( SoftwareSerial ) becasuse pin 13 was not PWM 
int bluePin = 9;


// sensor pins
int openSensorPin = 8;
int closeSensorPin = 7;
int liquidSesnorPin = 13;


// Initialize Stepper Motor
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 2, 3, 4, 5);

int  Steps2Take;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(A0, A1, A5, A4, A3, A2);

int delayTime2 = 350; // Delay between shifts (used by Scroll function)


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

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" INITIALISATION ");

  pinMode(bluePin,OUTPUT);  
  pinMode(greenPin,OUTPUT);
  pinMode(redPin,OUTPUT);
  
  pinMode(openSensorPin,INPUT);
  pinMode(closeSensorPin,INPUT);
  pinMode(liquidSesnorPin,INPUT);
  
 

  // Initialise the serial com
  Serial.begin(9600);  

  
  // Display info on LCD
  lcd.print(" INITIALISATION ");
  lcd.setCursor(0, 1);
  lcd.print("      DONE      ");
  small_stepper.setSpeed(600);  
  
 
}


 // function  to setup wifi system
void setupWiFi()
{
Serial.println("wifi setup");
  setColor(0, 0, 255); // turns on blue LED to indicate initialisation of system. 
  
  if (!testWithoutWiFi) { // added so quick testing can take place......
  ESP8266.begin(115200);
  sendToESP8266("AT+CIOBAUD=9600");
  receiveFromESP8266(4000);
  ESP8266.begin(9600);  
  InitESP8266();
  }
   // indicates system ready for internet connection
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
  //---------------------------------------------------

   setColor(255, 0, 0); // sets the led to red
}

void loop()
{

if (firstLoop) { // auto close when first booted up or there is emergency
  closeValve();
  firstLoop = false;
}

// ------------------------------- Checks to see if there is liquid in the chamber  ------------------------------ //

//----------------- POSSIBLE BUG BELOW WILL NEED TO BE CHANGED TO ACCOUNT FOR NORMAL LIQUID FLOW IN FINAL VERSION --------------------- 

  if (liquidSesnorPin==HIGH) // checks to see if float switch is triggered - ie there is liquid in the chamber
    {
    //  currentValveState = STATE_VALVE_CLOSED; // by pass untill sensor fitted
    //  SendData("full"); // sends message to website saying that the chamber is full 
    }
//------------------------------------------------  BUG ABOVE -------------------------------------------------------------


  // ------------------------------- Startup check gets the state of the valve ------------------------------ //
       

  if (currentValveState==STATE_VALVE_HALF) { // on first loop the current valve state will not be open or closed
      int currentState = checkValveState(); // gets the current state of valve  
      Serial.println("Current Valve State: ");
      Serial.print(currentState);

      switch(currentState) {
          case STATE_VALVE_OPEN: {       
          currentValveState = STATE_VALVE_OPEN;
          setColor(0, 255, 0); // sets led to green
          break;
          }
         case STATE_VALVE_CLOSED: {
         currentValveState = STATE_VALVE_CLOSED;
         setColor(255, 0, 0); // sets the led to red
         break;
         }
        case STATE_VALVE_HALF: {
        Serial.println("Closing Valve");
        closeValve(); // closes valve
        SendData("CLOSED"); // sents message to website saying that the valve is closed 
        break;
       }
      }
 }
 else {
  if (!wiFiSetDone) {
      setupWiFi();  
      wiFiSetDone = true;
  }
  else {

      if (testSend)
      {
        SendDataTest("Test");
        testSend = false;
      }
      else
      {
      mainLoop(); // runs the main loop
      }
  }
} 
}


void software_Reset() // Restarts program via software can be used to reset from website
{
asm volatile ("  jmp 0"); // software reset  
}  

void mainLoop()
{

  
  
 if(digitalRead(liquidSesnorPin)==HIGH) {
 
  lcd.setCursor(0, 0);
  lcd.print(" LIQUID ALERT! ");
//  SendData("LIQUID");
 }
 else {
  // Display info on LCD

  //print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
  // lcd.clear();
  // set the cursor to column 0, line 0 (line 1 is the second row, since counting begins with 0) 
  lcd.setCursor(0, 0);
  lcd.print(" LIQUID FLOWING  ");
  lcd.setCursor(0, 1);
  lcd.print(" \177 \177 \177 \177 \177 \177 \177 \177"); // Display arrow to the LCD screen (Octal)
 // delay(500);
 // lcd.setCursor(0, 1);
 // lcd.print("\177 \177 \177 \177 \177 \177 \177 \177 "); // Shift the arrows
 // delay(300);
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
      Serial.println("new client"); // Display info serial console
      int pinNumber = (ESP8266.read()-48); // get first number
      Serial.print("new pinNumber : "); // Display info serial console
      Serial.println(pinNumber, DEC);

      // If order 1 received: Open the valve
      if(pinNumber == 1) {
      
        setColor(255, 255, 50); // Turn the Led Amber
        valveMoving = true;

        // Display info on LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Contamination!");
        lcd.setCursor(0, 1);
        lcd.print("Valve Opening");
        openValve();  // Open Valve
        // Display info on LCD
        lcd.print("Valve Open!  ");
        SendData("OPEN");
      }

      // If order 2 received: Close the valve
      if(pinNumber == 2) {
        setColor(255, 255, 50); // Turn the Led Amber
        valveMoving = true;
        // Display info on LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Contamination");
        lcd.setCursor(0, 1);
        lcd.print("Valve closing");
        closeValve(); // Close Valve
        // Display info on LCD
        lcd.print("Valve closed!");
        SendData("CLOSED");
      }     

      // If order 3 received: send data to the server used for testing data
      if(pinNumber == 3) {      
//        ConnectToWebsite();  // Connect to the website
        SendData("Hello");  // Send data
      }  

      if(pinNumber == 4) {// valve test 
       boolean outputResults =  testValve();
     //  ConnectToWebsite();  // Connect to the website
     //  SendData("" + outputResults);  // Send data
      }     
      if(pinNumber == 5) {// system reset 
      software_Reset();
      }     
    }
  }   
}

boolean testValve()
{
  timeTestStart = millis();
  setColor(255, 0, 0);  // red
  delay(500);
  setColor(0, 255, 0);  // green
  delay(500);
  setColor(0, 0, 255);  // blue
  delay(500); 
  openValve();
  delay(2000);
  closeValve();
  return false; // code to be added here to test valve.
}


/* Function to initialise the ESP8266 */
void InitESP8266()
{  
  Serial.println("********************** INITIALISATION *********************"); 
  sendToESP8266("AT");
  receiveFromESP8266(2000);
  Serial.println("***********************************************************");
  sendToESP8266("AT+CWMODE=3"); //Wifi mode - softAP + station mode
  receiveFromESP8266(5000);
  Serial.println("***********************************************************");

  // Display info on LCD
  lcd.setCursor(0, 0);
  lcd.print("   CONNECTING   ");
  lcd.setCursor(0, 1);
  lcd.print("      WIFI      ");


  sendToESP8266("AT+CWJAP=\""+ wifiNetwork + "\",\"" + Password +"\""); //connect to wifi network
  receiveFromESP8266(15000);
  
  Serial.println("***********************************************************");
  sendToESP8266("AT+CIFSR"); //Display the IPs adress (client + server)
  
  receiveFromESP8266(15000,true);
 
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

// function to display output to LCD not used Yet
void sendLCD(String message, int line)
{
  if (line==0) {
     lcd.setCursor(0, 0);
     lcd.print(message);
  }
  else {
     lcd.setCursor(0, 1);
     lcd.print(message);
  }
}

/* Function to connect to the uni server */
void ConnectToWebsite1()
{
  Serial.println(".................. CONNECTION TO SERVER ....................");
  sendToESP8266("AT+CIPSTART=1,\"TCP\",\"mi-linux.wlv.ac.uk\",80"); //connect to website
  receiveFromESP8266(10000);

  Serial.println("***************** CONNECTION TO SERVER: OK ****************");
}


String id = "1837";
String zone = "c";
String site = "vbi";


void SendData(String data)
{
  data = "will=test"; // FOR DEBUG

  httppost (data,"mi-linux.wlv.ac.uk" , "/~1606512/NewWebUi/openvalve.php" ); 
}

void SendDataTest(String data)
{
  data = "will=test"; // FOR DEBUG
  httppost (data,"mi-linux.wlv.ac.uk" , "/~1606512/NewWebUi/startvalve.php" ); 
}



// sends http post

void httppost (String data, String server, String uri) { 


String dataL;
dataL = data.length();

  
ESP8266.println("AT+CIPSTART=1,\"TCP\",\"" + server + "\",80");//start a TCP connection. 
if(ESP8266.find("OK")) { 
Serial.println("TCP connection ready");
} delay(1000); 
String postRequest =
"POST " + uri + " HTTP/1.0\r\n" + 
"Host: " + server + "\r\n" + 
"Accept: *" + "/" + "*\r\n" + 
"Content-Length: " + dataL + "\r\n" + 
"Content-Type: application/x-www-form-urlencoded\r\n" + 
"\r\n" + data; 



String repL; 

repL = postRequest.length();


String sendCmd = "AT+CIPSEND=1,";//determine the number of caracters to be sent.
ESP8266.print(sendCmd); 
ESP8266.println(repL); 
 
receiveFromESP8266(5000);
//if(ESP8266.find(">")) { Serial.println("Sending..");
ESP8266.println(postRequest); 
 receiveFromESP8266(5000);
//}}
}

/* Function that send commands to the ESP8266 */
void sendToESP8266(String commande)
{  
  ESP8266.println(commande);
}



void receiveFromESP8266(const int timeout)
{
receiveFromESP8266(timeout, false);
}
/*Function that read and display messages sent by ESP8266 (with timeout)*/
void receiveFromESP8266(const int timeout, boolean LCD)
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
  String ipNumber = extractIP(reponse);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      WIFI      ");
  lcd.setCursor(0, 1);
  
  lcd.print(ipNumber);
  }
}


// gets the ip number from the responce string, NEEDS IMPROVING
String extractIP(String reponse)
{
  String ipNumber = "";
  int startIndex = reponse.indexOf("+CIFSR:STAIP,");
  startIndex = startIndex + 14;
  ipNumber = reponse.substring(startIndex);

  int endIndex = reponse.indexOf("+CIFSR:STAMAC");
  endIndex = endIndex -1;
  ipNumber = reponse.substring(startIndex, endIndex);

   // debugging lines
  //Serial.print(reponse); 
  //Serial.print(ipNumber); 
  
  // Display info on LCD  
  return ipNumber;
}



// A function to check if the valve has hit the limit switches, if not the stepper is moved forward once, if  limit swicth reached stepper is stopped.
boolean loopSteps(int numberOfSteps,boolean opening)
{
  int flashCount = 0;
  setColor(0, 0, 0);
       
  for(int i  = 0;i>numberOfSteps;i++) {// loops thro steps
    
      if (opening) {
        
         if(digitalRead(openSensorPin)) { // checks open limit switch
                 
           if(flashCount==flashEveryAmount){
          
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
          small_stepper.step(1);
          }
         else { 
           currentValveState = STATE_VALVE_OPEN;
           return false;
          }
       }
       else {  
        if(digitalRead(closeSensorPin)){ // checks closed limit switch
         
          if(flashCount==flashEveryAmount) {
          
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
         small_stepper.step(-1);
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
  for (int i = 0; i<8; i++){
    setColor(0, 0, 0); // Turn Off the Led
    if(!loopSteps(STEPS_PER_OUTPUT_REVOLUTION, true)){break;} // runs funtion to move stepper motor step bu step so that limit switch can be used - saves over run
  }  
  
  setColor(0, 255, 0); // Turn the Led Green
}

// Function to close the valve
void closeValve(){
  for (int i = 0; i<8; i++){
    setColor(0, 0, 0); // Turn Off the Led  
    if(!loopSteps(STEPS_PER_OUTPUT_REVOLUTION, false)){break;} // runs funtion to move stepper motor step bu step so that limit switch can be used - saves over run
  } 
  setColor(255, 0, 0); // Led turn red
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

// Function to scroll text on LCD (ex. of use: scrollInFromRight(1, "Line2 From Right");
void scrollInFromRight (int line, char str1[]) {

  int i = strlen(str1);

  for (int j = 16; j >= 0; j--) {
    lcd.setCursor(0, line);
      
    for (int k = 0; k <= 15; k++) {
      lcd.print(" "); // Clear line
    }

    lcd.setCursor(j, line);
    lcd.print(str1);
    delay(delayTime2);
  }
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



#include <SoftwareSerial.h>
#include <Stepper.h>
#include <LiquidCrystal.h>

#define DEBUG true

//---( Number of steps per revolution of INTERNAL motor in 4-step mode ) NOT USED
#define STEPS_PER_MOTOR_REVOLUTION 8   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION -2 * 64  //2048 

SoftwareSerial ESP8266(10, 11); // RX, TX

String wifiNetwork = "MOHAESP"; // Garder les guillemets
String Password = "password"; // Garder les guillemets

//String wifiNetwork = "lap_hotspot"; // Garder les guillemets
//String Password = "12345678"; // Garder les guillemets

boolean valveMoving = false;

int redPin = 13;
int greenPin = 12;
int bluePin = 9;

// Initialize Stepper Motor
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 2, 4, 3, 5);

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
  
  setColor(255, 0, 0); // Turn the RGB Led Red (Valve closed)

  // Initialise the serial com
  Serial.begin(9600);  
  ESP8266.begin(115200);
  sendToESP8266("AT+CIOBAUD=9600");
  receiveFromESP8266(4000);
  ESP8266.begin(9600);  
  InitESP8266();

  // Display info on LCD
  lcd.print(" INITIALISATION ");
  lcd.setCursor(0, 1);
  lcd.print("      DONE      ");
}


void loop()
{
  // Display info on LCD

  //print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
  // lcd.clear();
  // set the cursor to column 0, line 0 (line 1 is the second row, since counting begins with 0) 
  lcd.setCursor(0, 0);
  lcd.print("  GAS FLOWING   ");
  lcd.setCursor(0, 1);
  lcd.print(" \177 \177 \177 \177 \177 \177 \177 \177"); // Display arrow to the LCD screen (Octal)
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("\177 \177 \177 \177 \177 \177 \177 \177 "); // Shift the arrows
  delay(300);
 
  if(ESP8266.available()) // check if the esp is sending a message 
  {
    if(ESP8266.find("+IPD,")) // If network data received from a single connection
    {
      delay(500); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = ESP8266.read()-48; // subtract 48 because the read() function returns the ASCII decimal value
            
      ESP8266.find("pin="); // advance cursor to "pin="
      Serial.println("new client"); // Display info serial console
      int pinNumber = (ESP8266.read()-48); // get first number
      Serial.print("new pinNumber : "); // Display info serial console
      Serial.println(pinNumber, DEC);

      // If order 1 received: Open the valve
      if(pinNumber == 1)
      {      
        setColor(255, 255, 50); // Turn the Led Amber
        valveMoving = true;

        // Display info on LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Contamination!");
        lcd.setCursor(0, 1);
        lcd.print("Valve Opening");
        
        openValve();  // Open Valve

        // Display info on LCD
        lcd.print("Valve Open!  ");
      }

      // If order 2 received: Close the valve
      if(pinNumber == 2)
      {
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
        lcd.print("Valve close!");
      }     

      // If order 3 received: send data to the server
      if(pinNumber == 3)
      {
        ConnectToWebsite();  // Connect to the website
        SendData();  // Send data
      }      
    }
  }  
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


  // Display info on LCD
  lcd.setCursor(0, 0);
  lcd.print("      WIFI      ");
  lcd.setCursor(0, 1);
  lcd.print("   CONNECTED!   ");
  
  Serial.println("***********************************************************");
  sendToESP8266("AT+CIFSR"); //Display the IPs adress (client + server)
  receiveFromESP8266(15000);
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

/* Function to connect to the uni server */
void ConnectToWebsite()
{
  Serial.println(".................. CONNECTION TO SERVER ....................");
  sendToESP8266("AT+CIPSTART=1,\"TCP\",\"mi-linux.wlv.ac.uk\",80"); //connect to website
  receiveFromESP8266(10000);
  Serial.println("***************** CONNECTION TO SERVER: OK ****************");
}

// Function to send data by GET request
void SendData()
{
  sendToESP8266("AT+CIPSEND=1,109"); //send message to connection 1, 109 bytes (87 bytes before char "?")
  receiveFromESP8266(10000);

  String httpreq = "GET /~1613741/valve.php?will=hellofromArduino! HTTP/1.1";
  
  // Make a HTTP request:
  sendToESP8266(httpreq);
  receiveFromESP8266(10000);
  sendToESP8266("Host: mi-linux.wlv.ac.uk");
  sendToESP8266("Connection: keep-alive");
  sendToESP8266("");   
  receiveFromESP8266(10000);
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

// Function to open the valve
void openValve(){
  for (int i = 0; i<8; i++){
    setColor(0, 0, 0); // Turn Off the Led
    Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
    small_stepper.setSpeed(1000);   
    small_stepper.step(Steps2Take);
    //delay(10);
    setColor(255, 255, 50); // Turn the Led Amber
    Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CW 1 turn  
    small_stepper.setSpeed(1000);  // 700 a good max speed??
    small_stepper.step(Steps2Take);
  }  
  
  setColor(0, 255, 0); // Turn the Led Green
}

// Function to close the valve
void closeValve(){
  for (int i = 0; i<8; i++){
    setColor(0, 0, 0); // Turn Off the Led
    Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CCW 1 turn
    small_stepper.setSpeed(1000);   
    small_stepper.step(Steps2Take);
    //delay(10);
    setColor(255, 255, 50);
    Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CCW 1 turn  
    small_stepper.setSpeed(1000);  
    small_stepper.step(Steps2Take);
  }
  
  setColor(255, 0, 0); // Led turn red
}


// Function to set the RGB Led color
void setColor(int red, int green, int blue)
{
  // pin in analog and apply new value
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
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


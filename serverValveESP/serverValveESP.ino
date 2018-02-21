#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>



const char* ssid  = "lap_hotspot";
const char* password = "m0{C8520";

ESP8266WebServer server(80);


 
void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}


void handleRoot() {
  
  
  server.send(200, "text/plain", "hello from esp8266!");

String message = "";
 
  for (uint8_t i=0; i<server.args(); i++){
    message += server.arg(i);
  }
 writeString(message);
}

void handleNotFound(){
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
 
}



void setup(void){
  
  
  
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }


  if (MDNS.begin("esp8266")) {
   
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");


    
  });

  server.onNotFound(handleNotFound);

  server.begin();

}

void loop(void){
  server.handleClient();
}






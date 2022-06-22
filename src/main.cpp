#include <Arduino.h>
#include <wifi.h>
#include <autoconnect.h> 
#include <webserver.h> 
#include <WiFiManager.h>   


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  autoconnectSetup();
  webserverSetup();
}

void loop() {
 
 
}

#include <Arduino.h>
#include <wifi.h>
#include <autoconnect.h> 
#include <webserver.h>  


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  autoconnectSetup();
  wifiSetup();
  webserverSetup();

}

void loop() {
 
 
}

#include <Arduino.h>
#include <wifi.h>
#include <autoconnect.h>   


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  autoconnectSetup();
  wifiSetup();

}

void loop() {
  wifiLoop();
 
}

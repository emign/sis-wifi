#include <Arduino.h>
#include <webserver.h> 
#include <modbus.h>


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  webserverSetup();
  modbus_setup();
}

void loop() {  
    modbus_loop();    
}

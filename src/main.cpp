#include <Arduino.h>
#include <wifi.h>
#include <autoconnect.h> 
#include <webserver.h> 
#include <ESPAsyncWiFiManager.h>    
#include <modbus.h>


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  webserverSetup();
  modbus_setup();
}

void loop() {  
    modbus_loop();    
    WebSerial.println("Hello!");
    delay(2000); 
}

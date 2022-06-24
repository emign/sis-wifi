#include <Arduino.h>
#include <wifi.h>
#include <autoconnect.h> 
#include <webserver.h> 
#include <WiFiManager.h>   
#include <modbus.h>
#include <ota.h>


void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  autoconnectSetup();
  webserverSetup();
  ota_setup();
  modbus_setup();
}

void loop() {
  ArduinoOTA.handle();
  if (!_handlingOTA) {
    modbus_loop();
  } 
}

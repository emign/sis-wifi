#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>   
#include <WiFiManager.h>   

String header;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println("Starting...");
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("sis wifi");
  Serial.println("Connected.");


}

void loop() {
 
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);





  
}

#include <wifi.h>
#include <WiFiManager.h>   

void autoconnectSetup(){
  WiFiManager wifiManager;
  wifiManager.autoConnect("sis wifi");
  Serial.println("Connected to WiFi " + WiFi.SSID());
}
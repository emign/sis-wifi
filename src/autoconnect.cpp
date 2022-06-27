#include <ESPAsyncWiFiManager.h>    
#include <webserver.h>

#define WM_ASYNC 
static DNSServer dns;

void autoconnectSetup(){  
 
  Serial.println("Connected to WiFi " + WiFi.SSID());
  Serial.println("With IP: " + WiFi.localIP().toString());
}
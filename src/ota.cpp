#include <ota.h>



void ota_setup(){
    _handlingOTA = false;
    ArduinoOTA.setHostname("sis wifi ota");
    ArduinoOTA.begin();
    ArduinoOTA.onStart([]() {
    _handlingOTA = true;
  });
  
}
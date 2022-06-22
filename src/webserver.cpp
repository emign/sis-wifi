#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

static AsyncWebServer server(80);

void webserverSetup(){
    if (!LittleFS.begin()){
        Serial.println("FileSystem could not be mounted.");
        return;
    }
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, F("/index.html"), F("text/html"));
	});
    server.begin();
}
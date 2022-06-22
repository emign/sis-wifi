#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define WIFI_MANAGER_USE_ASYNC_WEB_SERVER

static AsyncWebServer server(80);



void webserverSetup(){
    if (!LittleFS.begin()){
        Serial.println("FileSystem could not be mounted.");
        return;
    }

    // Read registers.json to get the values of the registers
    File file = LittleFS.open("/registers.json", "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }
    String fileContent = file.readString();
    file.close();
    DynamicJsonDocument registers(8192);
    DeserializationError error =  deserializeJson(registers, fileContent);
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }
    for (JsonObject register_item : registers["register"].as<JsonArray>()) {
        int register_item_address = register_item["address"]; // 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, ...
        const char* register_item_rw = register_item["rw"]; // "rw", "r", "r", "r", "rw", "r", "r", "r", "r", ...
        int register_item_default = register_item["default"]; // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 5, 1, ...
        const char* register_item_description = register_item["description"]; // "Actual configured amps value ...

        String currentRegisterIn = "Register: " + String(register_item_address) + " " + register_item_rw + " " + String(register_item_default) + " " + register_item_description;

        const char* url = "/register/write/" + register_item_address;      

        server.on(url, HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});
    }
   
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/index.html", "text/html");
	});

  

    server.begin();
}
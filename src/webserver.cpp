#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <fileSystem.h>
#include <LittleFS.h>
#include <json.h>

#define WIFI_MANAGER_USE_ASYNC_WEB_SERVER
static AsyncWebServer server(80);
StaticJsonDocument<8192> doc;

void webserverSetup(){
    File file = open_file("registers.json", "r");
    read_json_file_to_doc(file, doc);
    

    for (JsonPair register_item : doc["registers"].as<JsonObject>()) {       
        // Create /register?nr=1000 like webhook and generate a JSON answer
        server.on("/register", HTTP_GET, [](AsyncWebServerRequest *request) {     
            if (request->args() == 0)
                return request->send(400, "text/plain", F("ERROR: Bad or no arguments"));  
            
            

            String register_nr  = request->arg("nr");         
            String rw           = request->arg("rw");
            String value        = request->arg("value");
            
            Serial.println("Value GET is set to: " + value);
            
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument json(1024);
            
            if (doc["registers"].containsKey(register_nr)) {
                json["nr"]          = register_nr;
                json["rw"]          = doc["registers"][register_nr]["rw"];
                json["value"]       = doc["registers"][register_nr]["value"];
                json["default"]     = doc["registers"][register_nr]["default"];
                json["description"] = doc["registers"][register_nr]["description"];
                serializeJson(json, *response);
                request->send(response);  	
            }
            else {
                json["error"] = "Register not found";
                serializeJson(json, *response);
                request->send(response);
            }
	});
    }
   
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/index.html", "text/html");
	});

  

    server.begin();
}


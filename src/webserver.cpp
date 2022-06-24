#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
//#include <AsyncElegantOTA.h>

#define WIFI_MANAGER_USE_ASYNC_WEB_SERVER

static AsyncWebServer server(80);
void insert_server_handlers();
StaticJsonDocument<8192> doc;


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
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    
    for (JsonPair register_item : doc["registers"].as<JsonObject>()) {       
        // Create /register?nr=1000 like webhook and generate a JSON answer
        server.on("/register", HTTP_GET, [](AsyncWebServerRequest *request) {     
            if (request->args() == 0)
                return request->send(400, "text/plain", F("ERROR: Bad or no arguments"));    
           
            String register_nr = request->arg("nr");         
            Serial.println("Register nr: " + String(register_nr));
            String rw = request->arg("rw");
            String value = request->arg("value");
            
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument json(1024);
            
            if (!request->arg("value").isEmpty()){
                // VALUE IS SET, WRITE TO REGISTER
                Serial.println("VALUE IS SET, WRITE TO REGISTER");
            }

            if (doc["registers"].containsKey(register_nr)) {
                json["nr"] = register_nr;
                json["rw"] = doc["registers"][register_nr]["rw"];
                json["value"] = doc["registers"][register_nr]["value"];
                json["default"] = doc["registers"][register_nr]["default"];
                json["description"] =doc["registers"][register_nr]["description"];
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

        server.on("/hallo2", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/index.html", "text/html");
	});

  
    //AsyncElegantOTA.begin(&server); 
    server.begin();
}


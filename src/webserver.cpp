#include <webserver.h>


#define WIFI_MANAGER_USE_ASYNC_WEB_SERVER

static AsyncWebServer server(80);
DynamicJsonDocument doc(8192);
DNSServer dns;

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
}

void webserverSetup(){
    AsyncWiFiManager wifiManager(&server, &dns);
    wifiManager.autoConnect("sis wifi");
    Serial.println("Connected to WiFi " + WiFi.SSID());
    Serial.println("With IP: " + WiFi.localIP().toString());

    //WebSerial.println("Connected to WiFi " + WiFi.SSID());
    //WebSerial.println("With IP: " + WiFi.localIP().toString());

    File file = open_file("registers.json", "r");
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

            String register_nr  = request->arg("nr");         
            String rw           = request->arg("rw");
            String value        = request->arg("value");
            
            Serial.println("Value GET is set to: " + value);
            
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            DynamicJsonDocument json(1024);
            
            if (!request->arg("value").isEmpty()){
                // VALUE IS SET, WRITE TO REGISTER
                Serial.println("VALUE IS SET, WRITE TO REGISTER");
            }

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

        server.on("/hallo2", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/index.html", "text/html");
	});

            server.on("/hallo32", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/index.html", "text/html");
	});

    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
    AsyncElegantOTA.begin(&server); 
    server.begin();
}


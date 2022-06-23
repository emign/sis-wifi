#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define WIFI_MANAGER_USE_ASYNC_WEB_SERVER

static AsyncWebServer server(80);
void insert_server_handlers();


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
    JsonArray registers_json = registers["register"].as<JsonArray>();
    for (JsonObject register_item : registers["register"].as<JsonArray>()) {
        int register_item_address = register_item["address"]; // 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, ...
        const char* register_item_rw = register_item["rw"]; // "rw", "r", "r", "r", "rw", "r", "r", "r", "r", ...
        int register_item_default = register_item["default"]; // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 5, 1, ...
        const char* register_item_description = register_item["description"]; // "Actual configured amps value ...

        String currentRegisterIn = "Register: " + String(register_item_address) + " " + register_item_rw + " " + String(register_item_default) + " " + register_item_description;

        const char* url = "/register/write/" + register_item_address;      

       

        insert_server_handlers();

    }
   
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/index.html", "text/html");
	});

  

    server.begin();
}

void insert_server_handlers(){

    //Actual configured amps value (from reg 2002 to 80A)
    server.on("/register/rw/1000", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");

     

       

	});

     //Actual amps value output 
    server.on("/register/r/1001", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});

    // Vehicle state
    server.on("/register/r/1002", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});

    // Maximum current limitation according to a cable based on PP resistor detection. 
    server.on("/register/r/1003", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});

    // bit0: turn off charging now
    // bit1: run selftest and RCD test procedure (approx 30s)
    // bit2: clear RCD error
    // bit3 bit15: not used
    server.on("/register/rw/1004", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});

    // Firmware revision
    server.on("/register/r/1005", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});

    // EVSE state
    server.on("/register/r/1006", HTTP_GET, [](AsyncWebServerRequest *request) {
		//request->send(LittleFS, "/index.html", "text/html");
        request->send(200, "text/plain", "TEDKDHJGKDHGK");
	});

    // EVSE status and fails
    server.on("/register/r/1007", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Error timeout
    server.on("/register/r/1008", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Selftest timeout
    server.on("/register/r/1009", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Reserved debug
    server.on("/register/r/1010", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Default amps value after boot (max 80A, min 6A)
    server.on("/register/rw/2000", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Function of PROG PIN 4 + 5, slave address
    server.on("/register/rw/2001", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Minimum amps value, allowed 0 13
    server.on("/register/rw/2002", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    // Analog input config
    server.on("/register/rw/2003", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps settings after power on
    server.on("/register/rw/2004", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Miscellaneous settings
    server.on("/register/rw/2005", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

     //RFU: Current sharing mode is active
    server.on("/register/rw/2006", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //PP Detection
    server.on("/register/rw/2007", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //reserved
    server.on("/register/rw/2008", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Bootloader Firmware version
    server.on("/register/r/2009", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 1
    server.on("/register/rw/2010", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 2
    server.on("/register/rw/2011", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 3
    server.on("/register/rw/2012", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 4
    server.on("/register/rw/2013", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 5
    server.on("/register/rw/2014", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 6
    server.on("/register/rw/2015", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 7
    server.on("/register/rw/2016", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

    //Amps Value 8
    server.on("/register/rw/2017", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "TEDKDHJGKDHGK");
    });

 
}
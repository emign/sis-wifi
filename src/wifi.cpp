#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>   

WiFiServer server(80);
String header = "";

void wifiSetup(){
    server.begin();
}
void wifiLoop(){
    WiFiClient client = server.available();

    if (client){
        Serial.println("New Client");
        String currentLine = "";
        while (client.connected()){
            char c = client.read();
            Serial.write(c);
            header += c;
             if (c== '\n'){
                 if (currentLine.length() == 0){
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();
                 }
              }
        }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
}
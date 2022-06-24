#include <json.h>

void read_json_file_to_doc(File file, StaticJsonDocument<8192> doc){
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
}
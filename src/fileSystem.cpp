#include <LittleFS.h>

/**
 * @brief Returns File Object of 
 * 
 * @return File 
 */
void _file_system_setup(){
    if (!LittleFS.begin()){
        Serial.println("FileSystem could not be mounted.");
        return;
    }    
}

File open_file(String file_name, char* read_mode){
    _file_system_setup();
    File file = LittleFS.open(file_name, read_mode);
    if (!file) {
        Serial.println("Failed to open file for reading");
    }
    return file;
}
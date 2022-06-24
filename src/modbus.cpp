#include <modbus.h>
// SoftwareSerial S(D1, D2, false, 256);
// receivePin, transmitPin, inverse_logic, bufSize, isrBufSize
// connect RX to D2 (GPIO4, Arduino pin 4), TX to D1 (GPIO5, Arduino pin 4)
SoftwareSerial S(4, 5); // RX, TX

ModbusRTU mb;
#define SLAVE_ID 1
#define REG_COUNT 2

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Callback to monitor errors
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
  }
  return true;
}

void modbus_setup() {
  //Serial.begin(115200);
 #if defined(ESP8266)
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S);
 #elif defined(ESP32)
  Serial1.begin(9600, SERIAL_8N1);
  mb.begin(&Serial1);
 #else
  Serial1.begin(9600, SERIAL_8N1);
  mb.begin(&Serial1);
  mb.setBaudrate(9600);
 #endif
  mb.master();
}


void modbus_loop() {
  if (!mb.slave()) { 
    uint16_t res[REG_COUNT];
    mb.readHreg(SLAVE_ID, 0, res, REG_COUNT, cb);
   while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }
    Serial.println(res[0]);
    Serial.println(res[1]);
  }
  delay(1000);

}
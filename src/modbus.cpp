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
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S);  
  mb.master();
}

uint16_t* read_registers(int nr, int reg_count = 1){
  uint16_t res[reg_count];
  if (!mb.slave()){    
    mb.readHreg(SLAVE_ID, 0, res, reg_count, cb);
    while(mb.slave()) { // Check if transaction is active
        mb.task();
        delay(10);
      }      
      //Serial.println(res[0]);
       WebSerial.println(res[0]);
  }
  return res;
}

void modbus_loop() {
  read_registers(1000);
  delay(1000);
}



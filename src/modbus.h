#include <ModbusRTU.h>
#include <SoftwareSerial.h>
#include <WebSerial.h>

void modbus_loop();
void modbus_setup();
int read_registers();
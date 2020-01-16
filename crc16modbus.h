
#ifndef DRIVERS_CRC16MODBUS_H_
#define DRIVERS_CRC16MODBUS_H_

#include <stdint.h>

#define CRC_POLY 0xA001
#define CRC_INITIAL 0xFFFF

unsigned int calculateCRC(unsigned char * data, unsigned char datalen);

#endif /* DRIVERS_CRC16MODBUS_H_ */

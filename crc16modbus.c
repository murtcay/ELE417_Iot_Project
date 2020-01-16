#include <msp430.h>
#include <stdint.h>
#include "crc16modbus.h"

unsigned int calculateCRC(unsigned char * data, unsigned char datalen){
    unsigned int crc = CRC_INITIAL;
    unsigned char i = 0;
    unsigned char j = 0;

    for(j = 0; j < datalen; j++){
        crc ^= (unsigned int)*(data+j);
        for (i = 0; i < 8; ++i) {
            if (crc & 1)
                crc = (crc >> 1) ^ CRC_POLY;
            else
                crc = (crc >> 1);
        }
    }

    return crc;
}

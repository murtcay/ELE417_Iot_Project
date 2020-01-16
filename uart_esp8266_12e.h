#ifndef __UART_ESP_8266_12e__
#define __UART_ESP_8266_12e__

void espSerialInit (void);
void espSerialTxData (unsigned char* sCmd);
void espSerialTxChar (unsigned char value);
void espClearReceivedOldData (void);
#endif

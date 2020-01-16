#ifndef __UART_HC06__
#define __UART_HC06__

void hc06SerialInit (void);
void hc06SerialTxChar ( char value);
void hc06SerialTxData ( char* sCmd);

#endif

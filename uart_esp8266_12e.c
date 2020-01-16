#include <msp430fr2433.h>
#include <stdint.h>
#include "uart_esp8266_12e.h"
//******************************************************************************************************************************************
char receivedData[400]={0};
unsigned int index=0;
//******************************************************************************************************************************************
void espSerialInit (void){
    P1SEL0 |= BIT4 | BIT5 ;                                              // P1.4 = TX    ,    P1.5 = RX

    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    UCA0BR0 = 6;                                                       // 1MHz SMCLK/9600 BAUD
    UCA0BR1 = 0x00;
    UCA0MCTLW = (0x2200 | UCOS16 | UCBRF_13 );
    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE &= ~UCRXIE;
}
//******************************************************************************************************************************************
void espSerialTxChar (unsigned char value){
    while(!(UCA0IFG & UCTXIFG));                                         // USCI_A0 TX buffer ready? Wait until it is.
        UCA0TXBUF = value;                                               // TX -> RXed character
}
//******************************************************************************************************************************************
void espSerialTxData (unsigned char* sCmd){
    while(*sCmd != '\0'){
        espSerialTxChar(*sCmd);
        sCmd++;
    }
    espSerialTxChar(*sCmd);
}
//******************************************************************************************************************************************
void espClearReceivedOldData (void){
    for(index=399; index > 0; index--){
        receivedData[index] = 0;
    }
    receivedData[0] = 0;
    index = 0;
}
//******************************************************************************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI0RX_ISR(void){
    receivedData[index++] = UCA0RXBUF;
    _BIC_SR_IRQ(LPM0_bits);
}

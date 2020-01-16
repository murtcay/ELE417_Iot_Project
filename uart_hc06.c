#include <msp430fr2433.h>
#include "uart_hc06.h"
unsigned char* bluetoothSerialCommand=0;
void hc06SerialInit (void){
    P2SEL0 |= (BIT5 | BIT6);                                        // P2.6 = TX    ,    P2.5 = RX
    UCA1CTLW0 |= UCSWRST;
    UCA1CTLW0 |= UCSSEL__SMCLK;

    UCA1BR0 = 6;
    UCA1BR1 = 0x00;
    UCA1MCTLW = (0x2200 | UCOS16 | UCBRF_13 );
    UCA1CTLW0 &= ~UCSWRST;
}

//******************************************************************************************************************************************
void hc06SerialTxChar (char value){
    while(!(UCA1IFG&UCTXIFG));                                         // USCI_A0 TX buffer ready? Wait until it is.
        UCA1TXBUF = value;                                               // TX -> RXed character
}

//******************************************************************************************************************************************
void hc06SerialTxData (char* sCmd){
    while(*sCmd != '\0'){
        hc06SerialTxChar(*sCmd);
        sCmd++;
    }
    hc06SerialTxChar(*sCmd);
}

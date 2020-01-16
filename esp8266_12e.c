#include <msp430fr2433.h>
#include "esp8266_12e.h"
#include "at_commands_esp.h"
#include "uart_esp8266_12e.h"
#include "crc16modbus.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "ssd1306_lib.h"
//******************************************************************************************************************************************
#define ssid "ELE417"
#define pwd "EmbeddeD"
//******************************************************************************************************************************************
volatile bool crcError = false;
extern unsigned int index;
extern unsigned char receivedData[400];
char espData[400]={0};
char parsedData[400]={0};
unsigned char request[5]= {GET_REQ, ' ', '\0'};
char* dataPtr;
//******************************************************************************************************************************************
void espInit(void){
    espSendCommand(AT, "OK", 75);
    espSendCommand(AT_CLOSE, "ERROR", 75);
    espSendCommand(AT_RESET, "ready", 2250);
    espSendCommand(AT_ATE0, "OK", 75);
    espSendCommand(AT_WIFI_MODE_3, "OK", 75);
    espSendCommand(AT_QUIT_AP, "OK", 100);
    espSendCommand(AT_SET_MUL_CON_0, "OK",75);
}
//******************************************************************************************************************************************
bool espConnectWifi(void){
    bool resp = false;
    while(!resp){
        resp = espSendCommand(AT_JOIN_AP_ELE417, "WIFI GOT IP", 5400);
    }
    return resp;
}
//******************************************************************************************************************************************
bool espConnectServer(void){
    bool resp = false;
    resp = espSendCommand(AT_START_CON_TCP, "OK", 700);
    if(resp && (strstr((const char *)espData, "ALREADY CONNECTED") == 0)){
        // send greeting message and control the response is hi or not
        // if it is hi this means first tcp connection
        // otherwise server is already connected
        espSendGreetingMsg();
    }
    return resp;
}
//******************************************************************************************************************************************
bool espGETData(unsigned char req_id){
	crcError = false;
    unsigned int resultCRC;
    request[1] = req_id;

    unsigned int m = 399;
    for(; m > 0; m--){  // CLEAR espData[]
        espData[m] = '\0';
    }
    espData[0] = '\0';
    if(espSendCommand(AT_SEND"=2\r\n",">",75)){                           // Check repsonse of SEND Command
        if(espSendCommand(request,"+IPD",600)){                           //  Check the Response is containing +IPD and CLOSED, if it contains we can PARSE it
            dataPtr = strstr(espData, "+IPD");
            dataPtr = strstr(dataPtr, ":");
            dataPtr = dataPtr+1;
            if(dataPtr[0] == req_id){
                volatile unsigned int msgLength= dataPtr[1];
                dataPtr[msgLength] = '\0';
                // CRC control
                resultCRC = calculateCRC((unsigned char*)dataPtr+2, msgLength-4);

                volatile unsigned int tempVal_CRC = 0;
                tempVal_CRC = (dataPtr[msgLength-2] << 8);
                tempVal_CRC |= (dataPtr[msgLength-1]);

                if(resultCRC == tempVal_CRC ){                              // message is correct
                    dataPtr[msgLength-2] = '\0';
                    dataPtr = dataPtr+2;
                    return true;
                }
                else{
                    crcError = true;
                }
            }
        }
    }
    return false;
}
//******************************************************************************************************************************************
bool espSendCommand(unsigned char* command, unsigned char* response, int time){
    espSerialTxData(command);
    UCA0IE |= UCRXIE;
    _BIS_SR(GIE);
    while(time--)
        __delay_cycles(900);
    UCA0IE &= ~UCRXIE;
    bool resp = strstr((char*)receivedData,(const char*) response) != 0;
    bool alreadyConnected = strstr((char*)receivedData, "ALREADY CONNECTED") != 0;
    if(!resp && alreadyConnected ){
        resp = alreadyConnected;
    }
    if(resp){
        for(; index > 0; index--){
            espData[index] = receivedData[index];                            // copy the receivedData to espData
            receivedData[index] = 0;
        }
        espData[0] = receivedData[0];
        receivedData[0] = 0;
        index = 0;
    }else
        espClearReceivedOldData();
    return resp;
}
//******************************************************************************************************************************************
void espSendGreetingMsg(){
    espSendCommand(AT_SEND"=2\r\n",">",75);
    espSendCommand("hi", "+IPD", 750);                                    // send the greeting message to server
}

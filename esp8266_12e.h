#ifndef __ESP_8266_12e__
#define __ESP_8266_12e__
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// Request IDs
#define TEMP_ID             0x01            // Temperature (�C) (Wheather)
#define PRESSURE_ID         0x02            // Air Pressure (hpa) (Wheather)
#define HUMIDITY_ID         0x03            // Humidity (%) (Wheather)
#define W_SPEED_ID          0x04            // Wind Speed (m/s) (Wheather)
#define CLOUDINESS_ID       0x05            // Cloudiness (%) (Wheather)
#define WHEATHER_STATUS_ID  0x06            // Wheather Status
#define CUR_TIME_ID         0x07            // Current Time (HH:MM:SS)
#define CUR_DATE_ID         0x08            // Current Date (YYYY/MM//DD)
#define UP_TIME_ID          0x09            // Uptime (Server)
#define SYST_TEMP_ID        0x0A            // System Temperature (�C) (Server)
#define NUM_OF_CLIENTS_ID   0x0B            // Connected # of Clients (Server)
#define GET_REQ             0xEE            // Get Data Request
#define GREETING_MSG_ID     0xFF            // Greeting message (for Testing)

// Functions
void espInit(void);
bool espConnectWifi(void);
bool espSendCommand(unsigned char* command, unsigned char* response, int time);
bool espConnectServer(void);
bool espGETData(unsigned char req_id);
void espSendGreetingMsg(void);

#endif

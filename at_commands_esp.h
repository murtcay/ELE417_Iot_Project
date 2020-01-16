#ifndef AT_COMMANDS_H
#define AT_COMMANDS_H

#define AT                  "AT\r\n"                    //
#define AT_ATE0             "ATE0\r\n"                  // serial echo disabled
#define AT_RESET            "AT+RST\r\n"                // restarts the ESP module
#define AT_WIFI_MODE_1      "AT+CWMODE=1\r\n"           // sets the wi-fi mode 1: Station mode
#define AT_WIFI_MODE_2      "AT+CWMODE=2\r\n"           // sets the wi-fi mode 2: SoftAP  mode
#define AT_WIFI_MODE_3      "AT+CWMODE=3\r\n"           // sets the wi-fi mode 3: SoftAP+Station mode
#define AT_JOIN_AP          "AT+CWJAP"                  // connects to an AP
#define AT_JOIN_AP_ELE417   "AT+CWJAP=\"ELE417\",\"EmbeddeD\"\r\n"      // connects to ELE417 AP
#define AT_LIST_AP          "AT+CWLAP\r\n"              // lists all available APs
#define AT_QUIT_AP          "AT+CWQAP\r\n"              // disconnects from an AP
#define AT_SET_AP_PARAMS    "AT+CWSAP"                  //
#define AT_GET_CON_STATUS   "AT+CIPSTATUS"              // gets the connection status
#define AT_START_CON_TCP    "AT+CIPSTART=\"TCP\",\"10.50.106.10\",10000\r\n"       // establishes TCP connection ip:10.50.106.10 port:10000
#define AT_SEND             "AT+CIPSEND"                // sends data
#define AT_CLOSE            "AT+CIPCLOSE\r\n"           // closes TCP/UDP/SSL connection
#define AT_SET_MUL_CON_0    "AT+CIPMUX=0\r\n"           // configures the connection modes and 0: single connection
#define AT_SET_MUL_CON_1    "AT+CIPMUX=1\r\n"           // configures the connection modes and 1: multiple connections
#define AT_SET_SERVER       "AT+CIPSERVER"              // deletes / creates a TCP server
#define AT_RECEIVED_DATA    "+IPD"                      // ESP receives network data

#endif

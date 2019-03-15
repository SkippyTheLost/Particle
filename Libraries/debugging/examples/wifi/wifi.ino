
#include "debugging.h"

SYSTEM_MODE(AUTOMATIC);

#define WIFI_SSID1 SSID1 // Put WiFi network SSID here.
#define WIFI_PASS1 PASS1 // Put WiFi network password here.

#define WIFI_SSID2 SSID2 // Put WiFi network SSID here.
#define WIFI_PASS2 PASS2 // Put WiFi network password here.

#define WIFI_SSID3 SSID3 // Put WiFi network SSID here.
#define WIFI_PASS3 PASS3 // Put WiFi network password here.

#define WIFI_SSID4 SSID4 // Put WiFi network SSID here.
#define WIFI_PASS4 PASS4 // Put WiFi network password here.

#define WIFI_SSID5 SSID5 // Put WiFi network SSID here.
#define WIFI_PASS5 PASS5 // Put WiFi network password here.

void setup() {
    debug.wifi();
}

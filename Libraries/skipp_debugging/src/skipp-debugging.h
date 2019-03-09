// -------- Debugging Library -------- {

#ifndef DEBUGGING
#define DEBUGGING

#include "Particle.h"

#if PLATFORM_ID == 0 // Core (0)
    #define SUPPORT_BLUETOOTH FALSE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH FALSE
    #define SUPPORT_WIFI TRUE
#endif

#if PLATFORM_ID == 6 // Photon (6)
    #define SUPPORT_BLUETOOTH FALSE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH FALSE
    #define SUPPORT_WIFI TRUE
#endif

#if PLATFORM_ID == 8 // P1 (8)
    #define SUPPORT_BLUETOOTH FALSE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH FALSE
    #define SUPPORT_WIFI TRUE
#endif

#if PLATFORM_ID == 10 // Electron (10)
    #define SUPPORT_BLUETOOTH FALSE
    #define SUPPORT_CELLULAR TRUE
    #define SUPPORT_MESH FALSE
    #define SUPPORT_WIFI FALSE
#endif

#if PLATFORM_ID == 12 // Argon (12)
    #define SUPPORT_BLUETOOTH TRUE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH TRUE
    #define SUPPORT_WIFI TRUE
#endif

#if PLATFORM_ID == 13 // Boron (13)
    #define SUPPORT_BLUETOOTH TRUE
    #define SUPPORT_CELLULAR TRUE
    #define SUPPORT_MESH TRUE
    #define SUPPORT_WIFI FALSE
#endif

#if PLATFORM_ID == 14 // Xenon (14)
    #define SUPPORT_BLUETOOTH TRUE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH TRUE
    #define SUPPORT_WIFI FALSE
#endif

#if PLATFORM_ID == 0 // Core (13)
    #define SUPPORT_BLUETOOTH TRUE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH TRUE
    #define SUPPORT_WIFI FALSE
#endif

#if PLATFORM_ID == 88 // Redbear Duo (88)
    #define SUPPORT_BLUETOOTH TRUE
    #define SUPPORT_CELLULAR FALSE
    #define SUPPORT_MESH FALSE
    #define SUPPORT_WIFI TRUE
#endif

class Debug { // debug
    public:
        Debug();
        float voltage = analogRead(BATT) * 0.0011224;
        double d_voltage = voltage;
        void
            begin(void) {
                Serial.begin();
                Particle.process();
                delay(100);
                Serial.printlnf("Device ID: %s", System.deviceID());
                Serial.printlnf("System Version: %s", System.version().c_str());
                Serial.printlnf("Free Memory: %i", System.freeMemory());
                
                #if SUPPORT_CELLULAR
                Serial.printlnf("Cellular: %s", Cellular.ready());
                #endif
                
                #if SUPPORT_MESH
                Serial.printlnf("Mesh: %s", Mesh.ready());
                #endif
                
                #if SUPPORT_WIFI
                Serial.printlnf("WiFi: %s", WiFi.ready());
                #endif
                
                Serial.printlnf("Ethernet: %s", Ethernet.ready());
                
                Serial.print("Particle Cloud: ");
                Serial.println(Particle.connected());
                
                Serial.print("Battery Voltage: ");
                Serial.printlnf("%fV", voltage);
            };
        bool
            print(String title, String data) {
                Serial.print(title);
                Serial.print(": ");
                Serial.println(data);
                
                #if SUPPORT_MESH
                Mesh.publish(title, data);
                #endif
                
                Particle.publish(title, data, 60, PRIVATE);
            };
        void
            wifi(void) {
                #if SUPPORT_WIFI
                    #ifdef WIFI_SSID1
                    WiFi.setCredentials(WIFI_SSID1, WIFI_PASS1);
                    #endif
                    #ifdef WIFI_SSID2
                    WiFi.setCredentials(WIFI_SSID2, WIFI_PASS2);
                    #endif
                    #ifdef WIFI_SSID3
                    WiFi.setCredentials(WIFI_SSID3, WIFI_PASS3);
                    #endif
                    #ifdef WIFI_SSID4
                    WiFi.setCredentials(WIFI_SSID4, WIFI_PASS4);
                    #endif
                    #ifdef WIFI_SSID5
                    WiFi.setCredentials(WIFI_SSID5, WIFI_PASS5);
                    #endif
                #endif
            };
};

Debug::Debug() { } Debug debug = Debug();

#endif

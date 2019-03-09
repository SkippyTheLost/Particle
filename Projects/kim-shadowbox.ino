// -------- Libraries -------- {

#include "debugging.h"
#include "Particle.h"
#include "neopixel.h"
#include "rgb_values.h"

// }

// -------- Preferances & Settings -------- {

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#define PIXEL_COUNT 19 // How many LEDs (Human number)
#define PIXEL_PIN D2 // D2 Recommended because reasons
#define PIXEL_TYPE WS2813 // I don't actually know, but this works
#define PIXEL_BRIGHTNESS 127 // (0 - 255)

#define SLEEP_PIN D0 // What the off switch is wired to

#define WIFI_SSID1 Bigpond827394
#define WIFI_PASS1 2E0FF0B0E0

// }

Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

class Scene { // scene
    public:
        Scene();
        String
            current = "normal";
        int
            update(String input) {
                current = input;
                return refresh();
            };
        int
            refresh(void) {
                if (current == "normal") {
                    normal();
                    return 0;
                } else if (current == "birthday") {
                    birthday();
                    return 1;
                } else if (current == "easter") {
                    easter();
                    return 2;
                } else if (current == "halloween") {
                    halloween();
                    return 3;
                } else if (current == "christmas") {
                    christmas();
                    return 4;
                } else if (current == "mixed") {
                    mixed();
                    return 5;
                } else {
                    normal();
                    return -1;
                }
            };
        void
            normal(void) {
                allLedsOn(RGB_ORANGE);
                /*
                // Castle
                pixels.setPixelColor( 0, RGB_ORANGE);
                pixels.setPixelColor( 1, 255, 172, 0);
                pixels.setPixelColor( 2, 255, 185, 0);
                pixels.setPixelColor( 3, 255, 198, 0);
                pixels.setPixelColor( 4, 255, 211, 0);
                pixels.setPixelColor( 5, 255, 224, 0);
                pixels.setPixelColor( 6, 255, 237, 0);
                pixels.setPixelColor( 7, RGB_YELLOW);
                
                // Cogsworth
                pixels.setPixelColor( 8, RGB_WHITE);
                
                // Lumiere
                pixels.setPixelColor( 9, RGB_WHITE);
                
                // Beauty & the Beast
                pixels.setPixelColor(10, RGB_WHITE);
                pixels.setPixelColor(11, RGB_WHITE);
                pixels.setPixelColor(12, RGB_WHITE);
                pixels.setPixelColor(13, RGB_WHITE);
                pixels.setPixelColor(14, RGB_WHITE);
                pixels.setPixelColor(15, RGB_WHITE);
                
                // Mrs. Potts & Chip
                pixels.setPixelColor(16, RGB_WHITE);
                pixels.setPixelColor(17, RGB_WHITE);
                
                // Rose
                pixels.setPixelColor(18, RGB_ORANGE);
                
                pixels.show();
                */
            };
        void
            birthday(void) {
                // Castle
                pixels.setPixelColor( 0, random(255), random(255), random(255));
                pixels.setPixelColor( 1, random(255), random(255), random(255));
                pixels.setPixelColor( 2, random(255), random(255), random(255));
                pixels.setPixelColor( 3, random(255), random(255), random(255));
                pixels.setPixelColor( 4, random(255), random(255), random(255));
                pixels.setPixelColor( 5, random(255), random(255), random(255));
                pixels.setPixelColor( 6, random(255), random(255), random(255));
                pixels.setPixelColor( 7, random(255), random(255), random(255));
                
                // Cogsworth
                pixels.setPixelColor( 8, random(255), random(255), random(255));
                
                // Lumiere
                pixels.setPixelColor( 9, random(255), random(255), random(255));
                
                // Beauty & the Beast
                pixels.setPixelColor(10, random(255), random(255), random(255));
                pixels.setPixelColor(11, random(255), random(255), random(255));
                pixels.setPixelColor(12, random(255), random(255), random(255));
                pixels.setPixelColor(13, random(255), random(255), random(255));
                pixels.setPixelColor(14, random(255), random(255), random(255));
                pixels.setPixelColor(15, random(255), random(255), random(255));
                
                // Mrs. Potts & Chip
                pixels.setPixelColor(16, random(255), random(255), random(255));
                pixels.setPixelColor(17, random(255), random(255), random(255));
                
                // Rose
                pixels.setPixelColor(18, random(255), random(255), random(255));
                
                pixels.show();
            };
        void
            easter(void) {
                
                
                pixels.show();
            };
        void
            halloween(void) {
                // Castle
                pixels.setPixelColor( 0, RGB_ORANGE);
                pixels.setPixelColor( 1, RGB_ORANGE);
                pixels.setPixelColor( 2, RGB_ORANGE);
                pixels.setPixelColor( 3, RGB_ORANGE);
                pixels.setPixelColor( 4, RGB_ORANGE);
                pixels.setPixelColor( 5, RGB_ORANGE);
                pixels.setPixelColor( 6, RGB_ORANGE);
                pixels.setPixelColor( 7, RGB_ORANGE);
                
                // Cogsworth
                pixels.setPixelColor( 8, RGB_WHITE);
                
                // Lumiere
                pixels.setPixelColor( 9, RGB_WHITE);
                
                // Beauty & the Beast
                pixels.setPixelColor(10, RGB_WHITE);
                pixels.setPixelColor(11, RGB_WHITE);
                pixels.setPixelColor(12, RGB_WHITE);
                pixels.setPixelColor(13, RGB_WHITE);
                pixels.setPixelColor(14, RGB_WHITE);
                pixels.setPixelColor(15, RGB_WHITE);
                
                // Mrs. Potts & Chip
                pixels.setPixelColor(16, RGB_WHITE);
                pixels.setPixelColor(17, RGB_WHITE);
                
                // Rose
                pixels.setPixelColor(18, RGB_ORANGE);
                
                pixels.show();
            };
        void
            christmas(void) {
                loopColor(RGB_RED);
                loopColor(RGB_GREEN);
                
                //pixels.show();
            };
        void
            mixed(void) {
                for (byte t_led = 0; t_led < PIXEL_COUNT; t_led++) {
                    pixels.setPixelColor(t_led, random(256), random(256), random(256));
                }
            };
}; Scene::Scene() { } Scene scene = Scene();


bool
    asleep = FALSE;

void setup() {
    pinMode(D7, OUTPUT); // Indicator LED
    
    pinMode(SLEEP_PIN, INPUT_PULLUP);
    attachInterrupt(SLEEP_PIN, sleep, CHANGE);
    if (digitalRead(SLEEP_PIN) == HIGH) { asleep = TRUE; digitalWrite(D7, LOW); } else digitalWrite(D7, LOW);
    
    /*
    pinMode(D1, OUTPUT);
    digitalWrite(D1, HIGH);
    */
    
    pixels.begin();
    pixels.setBrightness(PIXEL_BRIGHTNESS); // Brightness (0 - 255)
    pixels.show(); // Initialize pixels (Off)
    
    delay(1000);
    
    #if SUPPORT_CELLULAR
    Cellular.on();
    Cellular.connect();
    #endif
    
    #if SUPPORT_MESH
    Mesh.on();
    Mesh.connect();
    #endif
    
    #if SUPPORT_WIFI
    WiFi.on();
    WiFi.connect();
    #endif
    
    Particle.connect();
    
    Particle.function("Rattata", pingRattata);
    Particle.variable("Voltage", debug.d_voltage);
}

void loop() {
    if (!asleep) {
        // ---- PUT PATTERNS HERE ----
        scene.normal();
        
        #if SUPPORT_MESH
        Mesh.on();
        Mesh.connect();
        #endif
        
        while (!asleep) {
            Particle.process();
        }
    }
    if (asleep) {
        allLedsOff();
        pixels.setBrightness(PIXEL_BRIGHTNESS);
        
        #if SUPPORT_MESH
        // Mesh.off(); // **** CRASHES SYSTEM ****
        #endif
        
        while (asleep) {
            Particle.process();
        }
    }
}

void sleep(void) {
    if (digitalRead(SLEEP_PIN) == HIGH) { asleep = TRUE; pixels.setBrightness(0); digitalWrite(D7, LOW); }
    else { asleep = FALSE; pixels.setBrightness(PIXEL_BRIGHTNESS); digitalWrite(D7, HIGH); }
}

void allLedsOn(byte r, byte g, byte b) {
    for(uint16_t i=0; i<pixels.numPixels(); i++) {
        pixels.setPixelColor(i, r, g, b);
    }
    pixels.show();
}

void allLedsOff(void) {
    for(uint16_t i=0; i<pixels.numPixels(); i++) {
        pixels.setPixelColor(i, RGB_OFF);
        
    }
    pixels.show();
}

void loopColor(byte r, byte g, byte b) {
    for(uint16_t i=0; i<pixels.numPixels(); i++) {
        pixels.setPixelColor(i, r, g, b);
        pixels.show();
        delay(100);
    }
}

int pingRattata(String data) {
    /*
    char t_voltage[20];
    sprintf(t_voltage, "voltage = %2.4", debug.voltage);
    debug.print("Rattata_Voltage", t_voltage);
    */
    return TRUE;
}
// Libraries
#include <math.h>
#include <neopixel.h>
#include <rgb-values.h>

// Settings
#define PIXEL_COUNT 1
#define PIXEL_PIN D0

//#define PIXEL_TYPE WS2811
#define PIXEL_TYPE WS2812B
//#define PIXEL_TYPE WS2812B2
//#define PIXEL_TYPE WS2813
//#define PIXEL_TYPE SK6812RGBW

#define Argon_Deer "e00fce68c53ccfdee0b50daf"
#define Xenon_Walrus "e00fce6869b327e5ae5d0ec3"
#define Xenon_Dolphin "e00fce68c9aeec0865ba4f3b"
#define Xenon_Pidgeon "e00fce6804367d126b413dd6"
#define Xenon_Gerbil "e00fce68b7f8aef5886dee81"

#define DEVICE_COUNT 5

String deviceIndex[DEVICE_COUNT] = {
    Argon_Deer,
    Xenon_Walrus,
    Xenon_Dolphin,
    Xenon_Pidgeon,
    Xenon_Gerbil
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
    pinMode(D7, OUTPUT);
    
    byte deviceNo = GetDeviceNo();
    
    Particle.variable("DEVICE_NO", deviceNo);
    
    strip.begin();
    switch (deviceNo) {
        case 0: // Deer
            digitalWrite(D7, HIGH);
            break;
        case 1: // Walrus
            fade(RGB_BLUE, 1000, 1);
            break;
        case 2: // Dolphin
            fade(RGB_PURPLE, 1000, 1);
            break;
        case 3: // Pidgeon
            fade(RGB_GREEN, 1000, 1);
            break;
        case 4: // Gerbil
            fade(RGB_ORANGE, 1000, 1);
            break;
        default:
            set(RGB_WHITE);
            break;
    }
}

int GetDeviceNo() {
    for (int i = 0; i < DEVICE_COUNT; i++)
    {
        if (deviceIndex[i] == System.deviceID())
        {
            return i;
        }
    }
    return -1;
} // Returns Device Number based on the Device Index and the current Device's ID

void set(byte R, byte G, byte B) {
    for(int i=0; i < PIXEL_COUNT; i++) {
        strip.setPixelColor(i, R, G, B); // (Pixel number, Red, Green, Blue, [White])
    }
    strip.show();
} // Set all pixels to static color

void fade(int R, int G, int B, int steps, int sec) {
    int r = (R / steps);
    int g = (G / steps);
    int b = (B / steps);
    for (int j = 1; j < steps; j++) {
        for(int i=0; i < PIXEL_COUNT; i++) {
            strip.setPixelColor(i, r * j, g * j, b * j); // (Pixel number, Red, Green, Blue, [White])
        }
        strip.show();
        delay(sec);
    }
} // Fade in all pixels to static color
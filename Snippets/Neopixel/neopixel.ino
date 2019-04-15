// Libraries
#include "neopixel.h"
#include "rgb-values.h"

// Settings
#define PIXEL_COUNT 1
#define PIXEL_PIN D0

//#define PIXEL_TYPE WS2811
#define PIXEL_TYPE WS2812B
//#define PIXEL_TYPE WS2812B2
//#define PIXEL_TYPE WS2813
//#define PIXEL_TYPE SK6812RGBW

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
    strip.begin();
    set(RGB_WHITE);
}

void set(byte R, byte G, byte B) {
    for(int i=0; i < PIXEL_COUNT; i++) {
        strip.setPixelColor(i, R, G, B); // (Pixel number, Red, Green, Blue, [White])
    }
    strip.show();
} // Set all pixels to static color
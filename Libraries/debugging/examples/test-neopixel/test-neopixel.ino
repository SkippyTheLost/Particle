// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>


// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 8
#define PIXEL_PIN D2
#define PIXEL_TYPE SK6812RGBW // WS2811 // WS2812B // WS2812B2 // WS2813

#define PEACH 200,50,5
#define CYAN 10,150,70
#define PURPLE 180,3,180
#define BLUE 5,5,190
#define WHITE 150,150,150
#define GREEN 10,180,10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTime = 50;
int i;
void spin(int R, int G, int B);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
    //for(i=0; i < PIXEL_COUNT; i++) {
    //strip.setPixelColor(i, PURPLE);
    spin(WHITE);
    //strip.show(); }
    delay(1000);
}

void spin(int R, int G, int B) {
    for(i=0; i < PIXEL_COUNT; i++) {
        strip.setPixelColor(i, R,G,B, 0);
        strip.show();
        delay(waitTime);
    }
    for(i=0; i < PIXEL_COUNT; i++) {
        strip.setPixelColor(i, 0,0,0, 50);
        strip.show();
        delay(waitTime);
    }
}

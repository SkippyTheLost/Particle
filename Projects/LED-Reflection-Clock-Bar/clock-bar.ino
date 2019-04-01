#include <neopixel.h>
#include <math.h>

#define PIXEL_COUNT 12
#define PIXEL_PIN D3
#define PIXEL_TYPE WS2812B //WS2811

#define PEACH 200,50,5
#define CYAN 10,150,70
#define PURPLE 180,3,180
#define BLUE 5,5,190
#define WHITE 150,150,150
#define GREEN 10,180,10

// IMPORTANT: Set pixel COUNT, PIN and TYPE
//#define PIXEL_COUNT 60
//#define PIXEL_PIN D4
//#define PIXEL_TYPE WS2812B

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
//               note: if not specified, D2 is selected for you.
// Parameter 3 = pixel type [ WS2812, WS2812B, WS2811, TM1803 ]
//               note: if not specified, WS2812B is selected for you.
//               note: RGB order is automatically applied to WS2811,
//                     WS2812/WS2812B/TM1803 is GRB order.
//
// 800 KHz bitstream 800 KHz bitstream (most NeoPixel products ...
//                         ... WS2812 (6-pin part)/WS2812B (4-pin part) )
//
// 400 KHz bitstream (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//                   (Radio Shack Tri-Color LED Strip - TM1803 driver
//                    NOTE: RS Tri-Color LED's are grouped in sets of 3)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint16_t Hours = 4;
uint16_t Mins = 18;
uint16_t Seconds = 0;

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long lastSync = millis();
uint16_t LastMins;


void setup() {

    strip.begin();
    strip.clear();
    strip.show();
    
    strip.setBrightness(64);
    //
    // startup sequence
    //
    delay(500);
    colorWipe(strip.Color(255, 0, 0), 20); // Red
    colorWipe(strip.Color(0, 255, 0), 20); // Green
    colorWipe(strip.Color(0, 0, 255), 20); // Blue
    delay(500);

    LastMins = 61;   // Cause update on first run of the loop

    Time.zone(+10);
}

void loop()
{
    Hours = Time.hour();
    Mins = Time.minute();
    
    if(Mins != LastMins)
    {
        if(Mins == 0)   // Do a sequence every hour
        {
            //hourSequence();
        }
        strip.clear();

        setHours(Hours);
        setMins(Mins);
        
        strip.setPixelColor(0,255,255,255);

        strip.show();

        LastMins = Mins;
    }
    delay(10000);
}

void setHours(int hours)
{
    int16_t out;

    out = hours + 1;

    strip.setPixelColor(getOffset(out - 2), 20, 0, 0);
    strip.setPixelColor(getOffset(out - 1), 50, 0, 0);
    strip.setPixelColor(out, 255, 0, 0);
    strip.setPixelColor(getOffset(out + 1), 50, 0, 0);
    strip.setPixelColor(getOffset(out + 2), 20, 0, 0);
}

void setMins(int mins)
{
    int16_t out;

    out = map(mins, 0, 60, 1, 24);

    strip.setPixelColor(getOffset(out - 1), 0, 50, 0);
    strip.setPixelColor(out, 0, 255, 0);
    strip.setPixelColor(getOffset(out + 1), 0, 50, 0);
}


uint16_t getOffset(int16_t in)
{
    int16_t out = in;

    if(in < 1)
    {
        out = 24 + in;
    }
    else if(in > 24)
    {
        out = in - 24;
    }
    return out;
}
//
// Fill the dots one after the other with a color
//
void colorWipe(uint32_t c, uint8_t wait) {
    for(int16_t i=0; i <= PIXEL_COUNT; i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void hourSequence()
{
    strip.clear();

    colorWipe(strip.Color(255, 0, 0), 20); // Red
    colorWipe(strip.Color(0, 255, 0), 20); // Green
    colorWipe(strip.Color(0, 0, 255), 20); // Blue
    delay(500);
}

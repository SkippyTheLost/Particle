// System
SYSTEM_THREAD(ENABLED); // Keeps Mesh active without internet

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

#define FADE_SPEED 10

const char *PREFIX = "mesh-";

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
    Xenon_Gerbil};

int deviceNo = GetDeviceNo();

String deviceStatus[DEVICE_COUNT] = {
    "gateway",
    "off",
    "off",
    "off",
    "off"};

Adafruit_NeoPixel leds = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int red = 0;
int green = 0;
int blue = 0;

bool status = false;
bool connected = false;

void setup()
{
    Particle.function("Button", button);

    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);

    switch (deviceNo)
    {
    case 0: // Gateway - Deer
        Mesh.subscribe(PREFIX, meshHandler);

        pinMode(A0, INPUT_PULLUP);
        //attachInterrupt(A0, buttonInterrupt, RISING);
        break;
    default:
        leds.begin();
        leds.show();
        Mesh.subscribe(PREFIX + deviceIndex[deviceNo], deviceHandler);
        break;
    }
    Particle.connect();
}

void loop()
{
    if (Particle.connected() && Mesh.ready() && !connected)
    {
        digitalWrite(D7, LOW);
        connected = true;
    }

    switch (deviceNo)
    {
    case 0: // Gateway - Deer
        gateway();
        break;
    case 1:  // Walrus
    case 2:  // Dolphin
    case 3:  // Pidgeon
    case 4:  // Gerbil
    default: // If can't determine deviceNo

        break;
    }
    delay(1000);
    Particle.process();
}

String lastMeshEvent = "";
String lastMeshData = "";
void meshHandler(const char *event, const char *data)
{
    lastMeshEvent = event;
    lastMeshData = data;

    for (int i = 1; i < DEVICE_COUNT; i++)
    {
        if (lastMeshEvent == PREFIX + deviceIndex[i])
        {
            deviceStatus[i] = lastMeshData;
            return;
        }
    }
} // Gateway based calls

String lastEvent = "";
String lastData = "";
void deviceHandler(const char *event, const char *data)
{
    lastEvent = event;
    lastData = data;

    switch (deviceNo)
    {
    case 0: // Gateway - Deer

        break;
    default: // Anything but Gateway
        if (lastData == "command-on")
        {
            if (!status)
            {
                LED(true);
            }
            status = true;
            Mesh.publish(PREFIX + deviceIndex[deviceNo], "on");
        }
        else if (lastData == "command-off")
        {
            if (status)
            {
                LED(false);
            }
            status = false;
            Mesh.publish(PREFIX + deviceIndex[deviceNo], "off");
        }
        break;
    }
} // Device ID based calls

int button(String string)
{
    status = !status;
    return status ? 1 : 0;
}

int GetDeviceNo()
{
    for (int i = 0; i < DEVICE_COUNT; i++)
    {
        if (deviceIndex[i] == System.deviceID())
        {
            return i;
        }
    }
    return -1;
} // Returns Device Number based on the Device Index and the current Device's ID

void gateway()
{
    if (status)
    {
        for (int i = 1; i < DEVICE_COUNT; i++)
        {
            if (deviceStatus[i] == "off")
            {
                Mesh.publish(PREFIX + deviceIndex[i], "command-on");
                delay(5000);
            }
        }
    }
    else
    {
        for (int i = 1; i < DEVICE_COUNT; i++)
        {
            if (deviceStatus[i] == "on")
            {
                Mesh.publish(PREFIX + deviceIndex[i], "command-off");
                delay(5000);
            }
        }
    }
}

void LED(bool setTo)
{
    if (setTo)
    {
        switch (deviceNo)
        {
        case 0: // Deer
            digitalWrite(D7, HIGH);
            break;
        case 1: // Walrus
            fade(RGB_BLUE, FADE_SPEED);
            break;
        case 2: // Dolphin
            fade(RGB_PURPLE, FADE_SPEED);
            break;
        case 3: // Pidgeon
            fade(RGB_GREEN, FADE_SPEED);
            break;
        case 4: // Gerbil
            fade(RGB_ORANGE, FADE_SPEED);
            break;
        default:
            set(RGB_WHITE);
            break;
        }
    }
    else
    {
        {
            switch (deviceNo)
            {
            case 0: // Deer
                digitalWrite(D7, LOW);
                break;
            case 1: // Walrus
            case 2: // Dolphin
            case 3: // Pidgeon
            case 4: // Gerbil
            default:
                fade(RGB_OFF, FADE_SPEED);
                break;
            }
        }
    }
}

void set(byte R, byte G, byte B)
{
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        leds.setPixelColor(i, R, G, B); // (Pixel number, Red, Green, Blue, [White])
    }
    leds.show();
} // Set all pixels to static color

void fade(byte R, byte G, byte B, int speed)
{
    const int STEPS = 250;

    for (int j = 0; j < STEPS; j++)
    {
        for (int i = 0; i < PIXEL_COUNT; i++)
        {
            int curR = map(j, 0, STEPS, red, R);
            int curG = map(j, 0, STEPS, green, G);
            int curB = map(j, 0, STEPS, blue, B);

            leds.setPixelColor(i, curR, curG, curB); // (Pixel number, Red, Green, Blue, [White])
        }
        leds.show();
        delay(200 / speed);
    }

    red = R;
    green = G;
    blue = B;

    set(R, G, B);
} // Fade in all pixels to static color
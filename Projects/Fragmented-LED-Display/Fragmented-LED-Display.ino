// System
SYSTEM_THREAD(ENABLED); // 

// Libraries
#include "neopixel.h"   // Controls programmable LEDs
#include "rgb-values.h" // Simplifies RGB colors

// Settings
#define PIXEL_COUNT 1 // Integer - How many LEDs there are

#define PIXEL_PIN D0 // Pin - Where the LEDs data is wired

//#define PIXEL_TYPE WS2811
#define PIXEL_TYPE WS2812B
//#define PIXEL_TYPE WS2812B2
//#define PIXEL_TYPE WS2813
//#define PIXEL_TYPE SK6812RGBW

#define FADE_SPEED 10 // Integer - Fade processed as a (200 / FADE_SPEED) millisecond delay between each of the steps

#define SWITCH_PIN A0 // Pin - Where the switch is wired to the gateway

const char *PREFIX = "mesh-"; // String - Used as a prefix for all mesh calls

#define DEVICE_COUNT 5 // Integer - Total number of devices included

const String deviceIndex[DEVICE_COUNT] = {
    "e00fce68c53ccfdee0b50daf", // Argon_Deer - First device should be the gateway
    "e00fce6869b327e5ae5d0ec3", // Xenon_Walrus
    "e00fce68c9aeec0865ba4f3b", // Xenon_Dolphin
    "e00fce6804367d126b413dd6", // Xenon_Pidgeon
    "e00fce68b7f8aef5886dee81"  // Xenon_Gerbil
};
// String Array - Lists the Device ID of each device to assign them a number. 0 is the first entry in the list, and should always be the gateway.

String deviceStatus[DEVICE_COUNT] = {
    "gateway", // Argon Deer
    "off",     // Xenon_Walrus
    "off",     // Xenon_Dolphin
    "off",     // Xenon_Pidgeon
    "off"      // Xenon_Gerbil
};
// String Array to store the status of each device. Only used on the Gateway.

int deviceNo = GetDeviceNo(); // Sets the device number for each device based on deviceIndex[].

Adafruit_NeoPixel leds = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE); // Sets up the LEDs so that they can be controlled with a leds.function() call.

int color[3] = {0, 0, 0}; // Integer Array - Current Color. color[0] is red, color[1] is green, and color[2] is blue. No value should exceed 255.

bool status = false;    // Boolean - True when the current device's LED(s) are on or turning on.
bool connected = false; // Boolean - True after Mesh is connected and a connection to Paricle Cloud is established.

void setup()
{
    Particle.function("Button", button);

    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);

    switch (deviceNo)
    {
    case 0: // Gateway - Deer
        Mesh.subscribe(PREFIX, gatewayHandler); // Gateway recieves all event calls with PREFIX

        //Particle.variable("Gateway Status", deviceStatus[0]);

        Particle.variable("Device 1 Status", deviceStatus[1]);
        Particle.variable("Device 2 Status", deviceStatus[2]);
        Particle.variable("Device 3 Status", deviceStatus[3]);
        Particle.variable("Device 4 Status", deviceStatus[4]);

        pinMode(SWITCH_PIN, INPUT_PULLUP); // Sets up the input for the momentary push-button switch.
        //attachInterrupt(SWITCH_PIN, buttonInterrupt, RISING); // Attaches an interrupt to the momentary switch.
        break;
    default: // Every device except Gateway
        leds.begin(); // Prime the LEDs
        leds.show(); // Set the LEDs to off
        Mesh.subscribe(PREFIX + deviceIndex[deviceNo], deviceHandler); // Slave devices only recieves event calls with it's Device ID attached.
        break;
    }
    Particle.connect();
} // This runs once, immediately after the device turns on.

void loop()
{
    if (!connected && Particle.connected() && Mesh.ready())
    {
        digitalWrite(D7, LOW);
        connected = true;
    } // Uses the on-board LED to display when the device is connected to the Mesh and the Particle Cloud.

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
        // Only Gateway currently has functions in loop().
        break;
    }
    Particle.process();
    delay(1000);
} // This runs infinitely, immediately after the device turns on.

String lastEvent = ""; // String - Last Mesh event recieved
String lastData = "";  // String - Last Mesh data recieved

void gatewayHandler(const char *event, const char *data)
{
    lastEvent = event;
    lastData = data;

    for (int i = 1; i < DEVICE_COUNT; i++)
    {
        if (lastEvent == PREFIX + deviceIndex[i])
        {
            deviceStatus[i] = lastData;
            return;
        }
    }
} // Gateway based calls

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
        default: // No device number specific programming set
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
            case 1:  // Walrus
            case 2:  // Dolphin
            case 3:  // Pidgeon
            case 4:  // Gerbil
            default: // No device number specific programming set
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
            int curR = map(j, 0, STEPS, color[0], R);
            int curG = map(j, 0, STEPS, color[1], G);
            int curB = map(j, 0, STEPS, color[2], B);

            leds.setPixelColor(i, curR, curG, curB); // (Pixel number, Red, Green, Blue, [White])
        }
        leds.show();
        delay(200 / speed);
    }

    color[0] = R;
    color[1] = G;
    color[2] = B;

    set(R, G, B);
} // Fade in all pixels to static color
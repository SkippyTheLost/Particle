SYSTEM_THREAD(ENABLED); // Keeps Mesh active without internet

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

String deviceStatus[DEVICE_COUNT] = {
    "gateway",
    "off",
    "off",
    "off",
    "off"};

int deviceNo = GetDeviceNo();

bool onToggle = false;
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
        Mesh.subscribe(PREFIX + deviceIndex[deviceNo], deviceHandler);
        break;
    }
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
        if (onToggle)
        {
            for (int i = 1; i < DEVICE_COUNT; i++)
            {
                if (deviceStatus[i] == "off")
                {
                    Mesh.publish(PREFIX + deviceIndex[i], "command-on");
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
                }
            }
        }
        break;
    case 1: // Walrus

        break;
    case 2: // Dolphin

        break;
    case 3: // Pidgeon

        break;
    case 4: // Gerbil

        break;
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
            digitalWrite(D7, HIGH);
            onToggle = true;
            Mesh.publish(PREFIX + deviceIndex[deviceNo], "on");
        }
        else if (lastData == "command-off")
        {
            digitalWrite(D7, LOW);
            onToggle = false;
            Mesh.publish(PREFIX + deviceIndex[deviceNo], "off");
        }
        break;
    }
} // Device ID based calls

int button(String string)
{
    onToggle = !onToggle;
    return onToggle ? 1 : 0;
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

#define DEVICE_COUNT 4

String deviceIndex[DEVICE_COUNT] = {
    "deviceId0",
    "deviceId1",
    "deviceId2",
    "deviceId3"
};

void setup() {
    byte deviceNo = GetDeviceNo();
    
    Particle.variable("DEVICE_NO", deviceNo);
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
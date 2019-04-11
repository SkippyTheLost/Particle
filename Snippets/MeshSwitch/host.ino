const char *EVENT = "mesh";

String deviceStatus = "off";

String lastMeshEvent = "null";
String lastMeshData = "null";

bool onToggle = false;

void setup() {
    pinMode(D7, OUTPUT);
    
    Particle.variable("Event", lastMeshEvent);
    Particle.variable("Data", lastMeshData);
    
    Particle.variable("Status", deviceStatus);
    
    Particle.function("button", button);

    Mesh.subscribe(EVENT, meshHandler);
    
    pinMode(A0, INPUT_PULLUP);
    attachInterrupt(A0, buttonInterrupt, RISING);
}

void loop() {
    if (onToggle) {
        if (deviceStatus != "on") {
            
    }
    else {
        if (deviceStatus != "off") {
            
        }
    }
    delay(5000);
    }
}

void meshHandler(const char *event, const char *data) {
    deviceStatus = data;
    
    lastMeshEvent = event;
    lastMeshData = data;
}

int button(String string) {
    buttonInterrupt();
    return (onToggle) ? 1 : 0;
}

void buttonInterrupt() {
    onToggle = !onToggle;
    if (onToggle) {
        digitalWrite(D7, HIGH);
        Mesh.publish(EVENT, "command-on");
    }
    else {
        digitalWrite(D7, LOW);
        Mesh.publish(EVENT, "command-off");
    }
}
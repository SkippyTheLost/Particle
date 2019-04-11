const char *EVENT = "mesh";

bool onToggle = false;

String lastMeshEvent = "null";
String lastMeshData = "null";

void setup() {
    pinMode(D7, OUTPUT);
    
    Particle.variable("Event", lastMeshEvent);
    Particle.variable("Data", lastMeshData);
    
    Particle.variable("onToggle", onToggle);

    Mesh.subscribe(EVENT, deviceHandler);
}

void deviceHandler(const char *event, const char *data) {
    lastMeshEvent = event;
    lastMeshData = data;
    if (lastMeshData == "command-on") {
        digitalWrite(D7, HIGH);
        onToggle = true;
        Mesh.publish(EVENT, "on");
    }
    else if (lastMeshData == "command-off") {
        digitalWrite(D7, LOW);
        onToggle = false;
        Mesh.publish(EVENT, "off");
    }
    
}

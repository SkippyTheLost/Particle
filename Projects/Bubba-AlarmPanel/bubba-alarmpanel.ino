class Keypad {
    
    public:
    
        Keypad();
        
        int
            press(int i);
            
};

class Alarm {
    
    public:
    
        Alarm();
        
        int
        
            arm(void),
            
            disarm(byte user);
            
};

class Controller {
  public:
   Controller() { Particle.subscribe("Control", &Controller::controller, this); }
    void controller(const char *eventName, const char *data);
};

#define ARM_BUTTON 8
byte status = 0;


byte skipp_digit[4] = {1, 2, 3, 4}, skipp_length = arraySize(skipp_digit), skipp_count = 0;
byte steve_digit[4] = {0, 1, 2, 3}, steve_length = arraySize(steve_digit), steve_count = 0;


void setup() {
    
    Particle.variable("Status", status);
    
    Particle.function("RemoteAccess", remote);

//for(int i = 0; i < skipp_length; i++) {
    //skipp_digit[i] = skipp_code.substring(i, i+1);
//}

}

void loop() {
    
}

// -------- Keypad {
int Keypad::press(int i) {
    if(i == ARM_BUTTON) { arm(); }
    
    if(i == skipp_digit[skipp_count]) { skipp_count++; if(skipp_count == skipp_length) { disarm(8); } }
    else skipp_count = 0; if(i == skipp_digit[skipp_count]) { skipp_count++; }
    
    if(i == steve_digit[steve_count]) { steve_count++; if(steve_count == steve_length) { disarm(0); } }
    else steve_count = 0; if(i == steve_digit[skipp_count]) { steve_count++; }
}
// -------- }

// -------- Alarm {
int arm(void) {
    // ARMING SEQUENCE {
    // BEEP - LIGHT ON
    delay(5000);
    // BEEP - LIGHT OFF
    delay(5000);
    // BEEP - LIGHT
    delay(1000);
    // BEEP - LIGHT
    delay(1000);
    // BEEP - LIGHT
    delay(1000);
    // BEEP - LIGHT
    delay(1000);
    // BEEP - LIGHT
    delay(1000);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(500);
    // BEEP - LIGHT
    delay(250);
    // BEEP - LIGHT
    delay(250);
    // BEEP - LIGHT
    delay(250);
    // BEEP - LIGHT
    delay(250);
    // BEEP - LIGHT
    delay(250);
    // BEEP - LIGHT
    delay(250);
    // LONG BEEP }
    Particle.publish("ARMED", "", 60, PRIVATE); status = 1;
    return 1;
}

int disarm(int user) {
    switch (user) {
        case 8:
            Particle.publish("DISARMED", "Skippy", 60, PRIVATE); status = 0;
            return 1;
        case 0:
            Particle.publish("DISARMED", "Steve", 60, PRIVATE); status = 0;
            return 1;
        case -8:
            Particle.publish("SYSTEM", "OVERRIDE", 60, PRIVATE); status = 0;
            return -8;
        default:
            Particle.publish("STATUS", "INVALID USER", 60, PRIVATE);
            return -1;
    }
}

void beep(byte t) {
    // Beep and Light Flash
}

// -------- }

// -------- Remote {

int remote(String command) {
    if( command == "OVERRIDE" ) { disarm(-8); }
}

// -------- }
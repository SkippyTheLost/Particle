bool dst = -1;

void setup() {
    Particle.variable("DST", dst);
}

void loop() {
    dst = isDst(Time.day(), Time.month(), Time.weekday()); 
    delay(60 * 60 * 1000);
}

bool isDst(int day, int month, int dayOfWeek) {
    if (month < 4 || month > 10) { return TRUE; }
    else if (month > 4 && month < 10) { return FALSE; }
    else if (month == 4) {
        if (dayOfWeek >= day) { return TRUE; }
        else { return FALSE; }
    }
    else if (month == 10) {
        if (dayOfWeek >= day) { return FALSE; }
        else { return TRUE; }
    }
    return -1;
}
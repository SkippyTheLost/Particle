#include "photon-vbat.h"

// Parameters are:
// A7 = An unused pin that you are not normally analogReading from that's safe to pass to analogRead
// 6.54 = VBAT calibration constant (optional)
// 943 = temperature calibration constant (optional)
PhotonVBAT photonVBAT(A7, 1, 943);

void setup() {
	Serial.begin(9600);
}

void loop() {
	// Read battery voltage (in volts)
	float vbat = photonVBAT.readVBAT();

	// Read processor temperature (in degrees C)
	float tempC = photonVBAT.readTempC();

	float tempF = tempC * 9.0 / 5.0 + 32.0;

	Serial.printlnf("vbat=%f tempC=%f tempF=%f A0=%d", vbat, tempC, tempF, analogRead(A0));
	delay(1000);
}

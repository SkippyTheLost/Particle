// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>

#define location "TEST"
int mode = 0; //0 = Monitor, 1 = High, or -1 = Low

int
    safetemp = 5;

int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

int
    temperature = -127,
    temp = -127;

STARTUP(startup());

void startup() {
    
}

void setup() {
    Particle.variable(String(location), temperature);
    Particle.variable(String("Test_TEMP"), temp);
}

void loop() {
    temp = getTemp();
    if ( temperature > -127 ) {
        temperature = temp;
    }
    switch (mode) {
        case 0:
            
            break;
        case 1:
            //if()
            break;
    }
  delay(5000);
  
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
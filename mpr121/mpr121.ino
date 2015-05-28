#include "mpr121.h"
#include <Wire.h>

#define MAX_NOTES 9

int irqpin = 2;  // Digital 2
boolean touchStates[12]; //to keep track of the previous touch states

uint16_t HoleMask = 126; //0...001111110
uint16_t SixHolesAdd = 1; //0000.....1

int velocity = 100;
int noteON = 144; // 10010000
int noteOFF = 128; // 10000000


uint16_t notesIn[MAX_NOTES] = {127, 63, 31, 15, 7, 3, 1, 125, 13};
int notesOut[MAX_NOTES] = {50, 52, 54, 55, 57, 59, 61, 62, 60};

void setup() {

  pinMode(irqpin, INPUT);
  digitalWrite(irqpin, HIGH); //enable pullup resistor

  Serial.begin(57600);
  Wire.begin();

  mpr121_setup();
}

void loop() {
  readTouchInputs();
}

void sendMIDI(int command, int note, int velocity) {
  Serial.write(command);
  Serial.write(note);
  Serial.write(velocity);
}

void readTouchInputs() {
  if (!checkInterrupt()) {
    Wire.requestFrom(0x5A, 2); //read the touch state from the MPR121

    byte LSB = Wire.read();
    byte MSB = Wire.read();

    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states
    uint16_t note = (touched & HoleMask) | SixHolesAdd;

//    Serial.print("note ");
//    Serial.print(note);
//    Serial.println("");

    for (int i = 0; i < MAX_NOTES; i++)
    {
      if (notesIn[i] == note)
      {
        sendMIDI(noteON, notesOut[i], velocity);
        break;
      }
    }



    //    for (int i = 0; i < 12; i++) { // Check what electrodes were pressed
    //      if (touched & (1 << i)) {
    //
    //        if (touchStates[i] == 0) {
    //          //pin i was just touched
    //          Serial.print("pin ");
    //          Serial.print(i);
    //          Serial.println(" was just touched");
    //
    //        } else if (touchStates[i] == 1) {
    //          //pin i is still being touched
    //        }
    //
    //        touchStates[i] = 1;
    //      } else {
    //        if (touchStates[i] == 1) {
    //          Serial.print("pin ");
    //          Serial.print(i);
    //          Serial.println(" is no longer being touched");
    //
    //          //pin i is no longer being touched
    //        }
    //
    //        touchStates[i] = 0;
    //      }
    //
    //    }
  }
}




void mpr121_setup(void) {

  set_register(0x5A, ELE_CFG, 0x00);

  // Section A - Controls filtering when data is > baseline.
  set_register(0x5A, MHD_R, 0x01);
  set_register(0x5A, NHD_R, 0x01);
  set_register(0x5A, NCL_R, 0x00);
  set_register(0x5A, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5A, MHD_F, 0x01);
  set_register(0x5A, NHD_F, 0x01);
  set_register(0x5A, NCL_F, 0xFF);
  set_register(0x5A, FDL_F, 0x02);

  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5A, ELE0_T, TOU_THRESH);
  set_register(0x5A, ELE0_R, REL_THRESH);

  set_register(0x5A, ELE1_T, TOU_THRESH);
  set_register(0x5A, ELE1_R, REL_THRESH);

  set_register(0x5A, ELE2_T, TOU_THRESH);
  set_register(0x5A, ELE2_R, REL_THRESH);

  set_register(0x5A, ELE3_T, TOU_THRESH);
  set_register(0x5A, ELE3_R, REL_THRESH);

  set_register(0x5A, ELE4_T, TOU_THRESH);
  set_register(0x5A, ELE4_R, REL_THRESH);

  set_register(0x5A, ELE5_T, TOU_THRESH);
  set_register(0x5A, ELE5_R, REL_THRESH);

  set_register(0x5A, ELE6_T, TOU_THRESH);
  set_register(0x5A, ELE6_R, REL_THRESH);

  set_register(0x5A, ELE7_T, TOU_THRESH);
  set_register(0x5A, ELE7_R, REL_THRESH);

  set_register(0x5A, ELE8_T, TOU_THRESH);
  set_register(0x5A, ELE8_R, REL_THRESH);

  set_register(0x5A, ELE9_T, TOU_THRESH);
  set_register(0x5A, ELE9_R, REL_THRESH);

  set_register(0x5A, ELE10_T, TOU_THRESH);
  set_register(0x5A, ELE10_R, REL_THRESH);

  set_register(0x5A, ELE11_T, TOU_THRESH);
  set_register(0x5A, ELE11_R, REL_THRESH);

  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);

  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x0C);  // Enables all 12 Electrodes


  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5A, ATO_CFG0, 0x0B);
  set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V

  set_register(0x5A, ELE_CFG, 0x0C);

}


boolean checkInterrupt(void) {
  return digitalRead(irqpin);
}


void set_register(int address, unsigned char r, unsigned char v) {
  Wire.beginTransmission(address);
  Wire.write(r);
  Wire.write(v);
  Wire.endTransmission();
}

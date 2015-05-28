#include "mpr121.h"
#include <Wire.h>

#define MAX_NOTES 9
#define NOTEON 144
#define NOTEOFF 128

int irqpin = 2;  // Digital 2
boolean touchStates[12]; //to keep track of the previous touch states

const int ON_SWITCH = 6;
const int OCT_SWITCH = 7;

boolean lastOnState = LOW;
boolean currentOnState = LOW;
boolean lastOctState = LOW;
boolean currentOctState = LOW;

uint16_t HoleMask = 126; //0...001111110
uint16_t SixHolesAdd = 1; //0000.....1

int velocity = 100;

uint16_t notesIn[MAX_NOTES] = {127, 63, 31, 15, 7, 3, 1, 125, 13};
int notesOut[MAX_NOTES] = {50, 52, 54, 55, 57, 59, 61, 62, 60};
int maxNote = 69;

int latestNote;

boolean noteOn = LOW;
boolean noteOff = LOW;
boolean octave = LOW;

void setup()
{
  pinMode(irqpin, INPUT);
  pinMode (ON_SWITCH, INPUT);
  pinMode (OCT_SWITCH, INPUT);
  
  digitalWrite(irqpin, HIGH); //enable pullup resistor

  //Serial.begin(31250);
  Serial.begin(115200);
  Wire.begin();

  mpr121_setup();
}

void loop()
{
  // fill the latest note read from the holes (there's always one)
  updateNote();
  updateSwitch();
  
  // TODO: check blow sensor state
  
  int note = latestNote;
  
  if(octave)
  {
    note = min(latestNote + 12, maxNote);
  }
  
  if(noteOn)
  {
    sendMIDI(NOTEON, note, velocity);
    //noteOn = false;
  }
  
  if(noteOff)
  {
    sendMIDI(NOTEOFF, note, 0);
    noteOff = false;
    noteOn = false;
  }
}








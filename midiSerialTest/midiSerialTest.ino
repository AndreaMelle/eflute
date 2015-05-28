int velocity = 100;
int noteON = 144; // 10010000
int noteOFF = 128; // 10000000

void setup() {
  Serial.begin(31250);

}

void loop() {
  // from D3 to A4
  for (int note = 50; note < 70; note++) {
    sendMIDI(noteON, note, velocity);
    delay(300);
    sendMIDI(noteOFF, note, velocity);
    delay(200);
  }

}

void sendMIDI(int command, int note, int velocity) {
  Serial.write(command);
  Serial.write(note);
  Serial.write(velocity);
}

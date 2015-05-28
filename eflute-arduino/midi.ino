void sendMIDI(int command, int note, int velocity)
{
  Serial.write(command);
  Serial.write(note);
  Serial.write(velocity);
}

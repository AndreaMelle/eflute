const int BUTTON = 3;

boolean lastButton = LOW;
boolean currentButton = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode (BUTTON, INPUT);
}


boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if (last != current)
  {
    delay(5);
    current = digitalRead(BUTTON);
    return current;
  }
}

void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
  {
    Serial.println("ON");
  }
  else if(lastButton == HIGH && currentButton == LOW)
  {
    Serial.println("OFF");
  }

  lastButton = currentButton;
}

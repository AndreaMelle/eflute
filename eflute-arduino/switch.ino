boolean debounce(boolean last, int button)
{
  boolean current = digitalRead(button);
  if (last != current)
  {
    delay(5);
    current = digitalRead(button);
    return current;
  }
}

void updateSwitch()
{
  currentOnState = debounce(lastOnState, ON_SWITCH);
  currentOctState = debounce(lastOctState, OCT_SWITCH);
  
  if (lastOnState == LOW && currentOnState == HIGH) //if it was pressed...
  {
    noteOn = true;
  }
  else if(lastOnState == HIGH && currentOnState == LOW)
  {
    noteOff = true;
  }
  
  octave = currentOctState;

  lastOnState = currentOnState;
  lastOctState = currentOctState;
}

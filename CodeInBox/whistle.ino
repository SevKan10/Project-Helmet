void Whistle()
{
  int whistleState = digitalRead(whistlePin); // read the state of the whistle sensor.

  if (y >= 0.90 or y <= -0.90)
  { 
    (whistleState == 1);
  }
  else 
  {
     (whistleState == 0);
  }
}
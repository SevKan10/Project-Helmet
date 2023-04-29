void button()
{
   int buttonState = digitalRead(buttonPin); // read the state of the button.

  if (buttonState == HIGH) { // if button is pressed.
    digitalWrite(whistlePin,0); 
  } else { 
    digitalWrite(whistlePin,,1);
  }
}
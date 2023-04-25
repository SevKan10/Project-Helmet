void RelayinBox()
{
    digitalWrite(relayPin, HIGH); // turn on relay.
  delay(1000); // wait for a second.
  digitalWrite(relayPin, LOW); // turn off relay.
  delay(1000); // wait for a second.
 
}
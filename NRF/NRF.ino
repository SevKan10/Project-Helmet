void NRF()
{
  radio.startListening();
  while(!radio.available())
  {
    ping++; 
    if(ping/1000 > 250)
    {
      digitalWrite(Buzze, 0); digitalWrite(Power, 0);
      lcd.setCursor(0,0); lcd.print("Disconnected    ");
    }
  }
  radio.read(&data_receive, sizeof(package_receive)); 
  ping = 0;
}

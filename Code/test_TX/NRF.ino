void NRF()
{  
  radio.stopListening(); 
  data_send.TX_Connect = millis()/1000;
  data_send.SOS = digitalRead(SOS_btn);
  radio.write(&data_send, sizeof(package_send));

  radio.startListening();
  while(!radio.available())
  {
    ping++; 
    if(ping/1000 > 50)
    {
      lcd.setCursor(0,0); lcd.print("Lost connecting");
      digitalWrite(Buzze, 1);
    }
  }
  
  radio.read(&data_receive, sizeof(package_receive)); 
  if(data_receive.Call == 0)
  {
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("TX Calling!!!");
    Send_SOS();
  }
  ping = 0;
}

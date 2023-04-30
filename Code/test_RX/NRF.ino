void NRF()
{
  radio.stopListening(); 
  data_send.RX_Connect = millis()/1000;
  data_send.Call = digitalRead(Call_btn);
  radio.write(&data_send, sizeof(package_send));
 
  radio.startListening();
  while(!radio.available())
  {
    ping++; 
    if(ping/1000 > 50)
    {
      digitalWrite(Buzze, 1);
    }
  }
  radio.read(&data_receive, sizeof(package_receive)); 
  while(data_receive.SOS == 0){digitalWrite(Buzze, 1);}
//  Serial.print(data_receive.TX_Connect); Serial.print("  |  "); Serial.println(data_receive.SOS);
  ping = 0;
}

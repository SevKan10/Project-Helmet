void NRF()
{

  while(radio.available())
  {
    digitalWrite(Buzze, 0); digitalWrite(Power, 1);
    lcd.setCursor(0,0); lcd.print("Device Connected");
    radio.read(&data_receive, sizeof(package_receive)); 
    ping = 0; flag1=0;
  }
  while(!radio.available())
  {
    ping++; 
    if(ping/1000>50 && flag1==0)
    {
      digitalWrite(Buzze, 0); digitalWrite(Power, 0);
      lcd.setCursor(0,0); lcd.print("Disconnected    ");

      char customKey = customKeypad.getKey();
      if (customKey && flag1==0 ){
        lcd.clear();
        data+=customKey;
        if(customKey=='C'){data="";}
        lcd.setCursor(0,1); lcd.print(data);  
      }

      if(data==PW)
      {
        lcd.clear(); lcd.setCursor(0,0); lcd.print("Correct password"); flag1=1;
        while(data==PW)
        {
          char Key = customKeypad.getKey(); 
          while(Key=='A')  { lcd.setCursor(0,1); lcd.print("Unlocked"); digitalWrite(Power, 1); }
          while(Key=='D')  
          { 
            lcd.setCursor(0,0); lcd.print("Reset password  ");
            char pass = customKeypad.getKey(); 
            if(pass)
            {
              lcd.clear(); 
              datas+=pass; 
              if(pass=='C'){datas="";}
              lcd.setCursor(0,1); lcd.print(datas);
              if(pass=='A'){for (int i = 0; i < datas.length(); ++i){EEPROM.write(i, datas[i]);} delay(500); resetFunc();}
            }  
          }
        }
      }  
    }  
  }
}

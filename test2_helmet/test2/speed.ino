void Speed(void)
{
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 300;)
  {
    while (gpsSerial.available() > 0)
    {
      if (gps.encode(gpsSerial.read()))
      {
        newData = true;
      }
    }
  }
 
  if (newData == true)
  {
    newData = false; 
    if (gps.location.isValid() == 1)
    {
      Serial.print("Sat ");
      Serial.println(gps.satellites.value());
      
      if (gps.speed.kmph() > 40) {
        digitalWrite(Buzz, 1);
        delay(200);
        digitalWrite(Buzz, 0);
  
        simSerial.listen();
        simSerial.println("AT+CMGF=1");
        delay(500);
        simSerial.println("AT+CMGS=\"" + ADMIN + "\"\r");
        delay(500);
        simSerial.println("Excessive speed > 40km/h");
        simSerial.println((char)26);
        delay(2000);
        simSerial.stopListening(); 

    }
    }
  }
}



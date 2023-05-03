void GPS(void)
{
  //Tốc độ
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 300;) {
    while (SoftSerial.available() > 0) {
      if (gps.encode(SoftSerial.read())) {
        newData = true;
      }
    }
  }

  //If newData is true
  if (newData == true) {
    newData = false;
    (gps.location.isValid() == 1);
    {
      Serial.print("Speed ");
      Serial.println(gps.speed.kmph());
      Serial.print(" km/h");

      Serial.print("Sat ");
      Serial.println(gps.satellites.value());
    }
  }
  //Tọa độ
   while (SoftSerial.available() > 0) 
  {
    if (gps.encode(SoftSerial.read())) 
    {
      if (gps.location.isValid()) 
      {
        Serial.print("Latitude   = ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude  = ");
        Serial.println(gps.location.lng(), 6);
      } 
    }
  }

}
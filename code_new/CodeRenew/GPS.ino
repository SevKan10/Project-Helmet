void GPS(void)// Chương trình con GPS tính tốc độ
{
  //-------------------------------------------------------------
    boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 300;) {
    while (SoftSerial.available() > 0) {
      if (gps.encode(SoftSerial.read())) {
        newData = true;
      }
    }
  }

  //If newData is true
  if (newData == true) 
  {
    newData = false;
    (gps.location.isValid() == 1);
    {
      Serial.print("Speed ");
      Serial.print(gps.speed.kmph());
      Serial.println(" km/h");
      //In ra tốc độ
      Serial.print("Sat ");
      Serial.println(gps.satellites.value());
      //In ra vệ tinh
    }
  }
  //Hàm tính tốc độ
  //------------------------------------------------------------------
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
      else 
      {
        Serial.println("Location Invalid");
      }
      if (gps.satellites.isValid()) 
      {
        Serial.print("Satellites = ");
        Serial.println(gps.satellites.value());
      } 
      else
      {
        Serial.println("Satellites Invalid");
      }  
    }
  }//Hàm tính tốc độ
  //-------------------------------------------------------------------
      if (gps.speed.kmph() > 40) 
    {
    Serial.println("Quá tốc độ");
    delay(500);
    } 
    else
    {
      Serial.println("Tốc độ bình thường");
      delay(1000);
    }
  // Lệnh If dùng để giới hạn tốc độ
  //-------------------------------------------------------------------
}
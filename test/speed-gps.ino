void getGps(void) {
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
      lcd.setCursor(0, 0);
      lcd.print(gps.speed.kmph());
      delay(100);
      Serial.print("Speed ");
      Serial.println(gps.speed.kmph());
      lcd.print(" km/h");

      lcd.setCursor(0, 1);
      lcd.print(gps.satellites.value());
      lcd.print(" SAT");
      delay(100);
      Serial.print("Sat ");
      Serial.println(gps.satellites.value());
    }
  }
}
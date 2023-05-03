void mpu() {
  // XỬ LÝ DỮ LIỆU MPU6050 VÀ VỊ TRÍ GPS
  while (SoftSerial.available() > 0) {
    if (gps.encode(SoftSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print("Latitude   = ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude  = ");
        Serial.println(gps.location.lng(), 6);
      } else {
        Serial.println("Location Invalid");
      }
      if (gps.satellites.isValid()) {
        Serial.print("Satellites = ");
        Serial.println(gps.satellites.value());
      } else
        Serial.println("Satellites Invalid");
    }
  }

  mpu6050.update();
  float y = mpu6050.getAccY();
  Serial.println("Value MPU6056");
  Serial.print("\ty: ");
  Serial.println(y);
  delay(10);
  // Lấy giá trị y để xác định
if (y >= 0.70 or y <= -0.70)
 {
  String url = "http://maps.google.com/maps?q=loc:";
  url = url + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
  digitalWrite(redled, 1);
  Serial.println(url);
  Serial.println("xe bi nga ");
  lcd.setCursor(0, 0);
  lcd.print(url);
  lcd.clear();
  delay(500);
  digitalWrite(whistlePin,1);
  // digitalWrite(relay,1); test relay

    mySim.println("AT+CMGF=1");   // text mode on
  delay(1000);                      
  mySim.println("AT+CMGS=\"+84\"\r"); 
  delay(1000);
  mySim.println(url);
  delay(100);
  mySim.println((char)26);
  delay(1000);
}
else 
{
  digitalWrite(redled, 0);
  digitalWrite(whistlePin,0);
  // digitalWrite(relay,0); test relay
}
}

   
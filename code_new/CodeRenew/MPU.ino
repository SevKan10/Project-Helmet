void MPU() // Chương trình con MPU 
{
  //-----------------------------------
  mpu6050.update();
  float y = mpu6050.getAccY();
  Serial.println("Value MPU6050");
  Serial.print("\ty: ");
  Serial.println(y);
  delay(10); 
  // Lấy giá trị góc để xác định khi ngã
  //-------------------------------------
    GPS();// Gọi chương trình con GPS để lấy tọa độ khi ngã
      if (y >= 0.70 or y <= -0.70) 
      {
      String URL = "http://maps.google.com/maps?q=loc:";
      URL = URL + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
      Serial.println(URL);
      Serial.println("Xe bị ngã");
      delay(500);
      } 
      else 
      {
      Serial.println("Xe bình thường");
      delay(500);
      }
  //---------------------------------------
}
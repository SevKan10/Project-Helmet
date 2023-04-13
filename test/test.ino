#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
#include <Wire.h>
#include <GOFi2cOLED.h>
GOFi2cOLED oled;
int Brightness = 0;
#include <TinyGPS++.h>          
#include <SoftwareSerial.h>   
TinyGPSPlus gps;
#define S_RX    8                
#define S_TX    9      
SoftwareSerial SoftSerial(S_RX, S_TX);
boolean yellowled = 13;
boolean redled = 12;
boolean greenled = 11;
void setup()
 
 {
   Serial.begin(9600);
   SoftSerial.begin(9600); 
   Wire.begin();
   mpu6050.begin();
   mpu6050.calcGyroOffsets(true);
   pinMode(yellowled,OUTPUT);
   pinMode(redled,OUTPUT);
   pinMode(greenled,OUTPUT);
   yellowled = 0;
   redled = 0;
   greenled = 0;
 }

void loop()

 {
   // XỬ LÝ DỮ LIỆU CẢM BIẾN GPS
   boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 300;)
  {
    while (SoftSerial.available() > 0)
    {
      if (gps.encode(SoftSerial.read()))
      {
        newData = true;
      }
    }
  }
  // Tính vận tốc
  if (newData == true)
  {
    newData = false; 
    (gps.location.isValid() == 1);
    {
      Serial.print("Speed: ");
      Serial.print(gps.speed.kmph());
      Serial.println("Km/h"); 
      // In ra tốc độ 
      Serial.print("Sattlites: ");
      Serial.println(gps.satellites.value());
      // In ra số vệ tinh
     
    }
  if (gps.speed.kmph()>40) 
  {
      digitalWrite(yellowled,1);
  }
    // Nếu xe chạy trên 40km/h thì đèn vàng sẽ sáng
  }
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
        Serial.println("Satellites Invalid");
    } 
  }
    

    // XỬ LÝ DỮ LIỆU MPU6050
     mpu6050.update();
     float x= mpu6050.getAccX();
     float y = mpu6050.getAccY();
     float z = mpu6050.getAccZ();
     Serial.println("Value MPU6056");
     Serial.print("x: "); Serial.print(x);
     Serial.print("\ty: "); Serial.print(y);
     Serial.print("\tz: "); Serial.println(z);
     delay(200);
     // Lấy giá trị y để xác định
    if (y>0.90)
     {
         String url = "http://maps.google.com/maps?q=loc:";
      url = url + String(gps.location.lat(), DEC) + "," + String(gps.location.lng(), DEC);
    
      Serial.println(url);
      Serial.println("xe bi nga ");
      digitalWrite(redled,1);
     }
    // Nếu y có giá trị trên 90 thì xe ngã khi đó đèn đỏ sáng 
//**************************************************
 }
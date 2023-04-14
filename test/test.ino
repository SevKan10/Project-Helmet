#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
MPU6050 mpu6050(Wire);
#include <TinyGPS++.h>          
#include <SoftwareSerial.h>   
TinyGPSPlus gps;
#define S_RX    8                
#define S_TX    9      
SoftwareSerial SoftSerial(S_RX, S_TX);
int yellowled = 13; // for speed
int redled = 12; // for mpu
void setup()
 
 {
   Serial.begin(9600);
   lcd.init();
   lcd.backlight();
   mpu6050.begin();
   mpu6050.calcGyroOffsets(true);
  SoftSerial.begin(9600); 
  pinMode(yellowled,OUTPUT);
  pinMode(redled,OUTPUT);

 }

void loop()

 {
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
 
  //If newData is true
  if (newData == true)
  {
    newData = false; 
    (gps.location.isValid() == 1);
    {
      //String gps_speed = String(gps.speed.kmph());
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
    if (gps.speed.kmph()>=11)
    {
      digitalWrite(yellowled,1);
    }
    else
     digitalWrite(yellowled,0);
  }

    // XỬ LÝ DỮ LIỆU MPU6050 VÀ VỊ TRÍ GPS
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
      if (gps.satellites.isValid()) {
        Serial.print("Satellites = ");
        Serial.println(gps.satellites.value());
      }
      else
        Serial.println("Satellites Invalid");
      }  
      }

     mpu6050.update();
     float y = mpu6050.getAccY();
     Serial.println("Value MPU6056");
     Serial.print("\ty: "); Serial.println(y);
     delay(10);
     // Lấy giá trị y để xác định
    if (y>=0.90 or y<=-0.90)
     {
      String url = "http://maps.google.com/maps?q=loc:";
      url = url + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
      digitalWrite(redled,1);
      Serial.println(url);
      Serial.println("xe bi nga ");
      lcd.setCursor(0,0);
      lcd.print(url);
      lcd.clear();
      delay(500);
     }
     else 
     {
          digitalWrite(redled,0);
     }
    // Nếu y có giá trị trên 90 thì xe ngã khi đó đèn đỏ sáng 
//**************************************************
  }
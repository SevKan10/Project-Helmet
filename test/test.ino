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
 gps()
  {
    if (gps.speed.kmph()>=11)
    {
      digitalWrite(yellowled,1);
    }
    else
      digitalWrite(yellowled,0);
  }
   mpu()
  {
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
  }
}


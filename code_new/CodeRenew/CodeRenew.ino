//-------------------------MPU
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
//--------------------------GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
#define S_RX 8
#define S_TX 9
SoftwareSerial SoftSerial(S_RX, S_TX);
void setup()
{
  Serial.begin(9600);
  //---------------------------
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  //----------------------------
  SoftSerial.begin(9600);
}

void loop()
{
  //----------------------------------------------
  GPS();// Gọi chương trình con GPS tính tốc độ
  //-----------------------------------------------
  MPU();// Gọi chương trình con MPU
}
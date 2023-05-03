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
//---------------------------SIM
SoftwareSerial mySerial(9, 10);
char msg;
char call;
void setup()
{
  Serial.begin(9600);

  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  SoftSerial.begin(9600);

  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.println("GSM SIM900A BEGIN");
  delay(100);
}

void loop()
{
  GPS();
  MPU();
  SIM();
  


}

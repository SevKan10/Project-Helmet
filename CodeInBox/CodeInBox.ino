#include <MPU6050_tockn.h>
#include <Wire.h>
// mpu
#include <LiquidCrystal_I2C.h>  //lcd i2c
LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu6050(Wire);
#include <TinyGPS++.h> // gps
#include <SoftwareSerial.h>
TinyGPSPlus gps;
#define S_RX 8
#define S_TX 9
SoftwareSerial SoftSerial(S_RX, S_TX);
#include <SPI.h>
#include "RF24.h" //rf
const uint64_t pipe = 0xE8E8F0F0E1LL; // địa chỉ để phát
RF24 radio(9,10);//thay 10 thành 53 với mega
byte msg[3];
const int relayPin = 8; //relay use with rf
int yellowled = 13;  // for speed
int redled = 12;     // for mpu
int buttonPin = 2; //button
int whistlePin = 11; //còi
void setup()

{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  SoftSerial.begin(9600);
  pinMode(yellowled, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(relayPin, OUTPUT); 
  pinMode(buttonPin, INPUT);
  pinMode(whistlePin, INPUT);
  radio.begin();                     
  radio.setAutoAck(1);              
  radio.setDataRate(RF24_1MBPS);    // Tốc độ dữ liệu
  radio.setChannel(10);               // Đặt kênh
  radio.openReadingPipe(1,pipe);     
  radio.startListening();            
  
}
void loop() {
  getGps();

  if (gps.speed.kmph() >40) {
    digitalWrite(yellowled, 1);
  } else
    digitalWrite(yellowled, 0);

  mpu();
  RfinBox();
  RelayBox();
  button();
}

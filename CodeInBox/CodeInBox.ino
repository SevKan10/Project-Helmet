#include <MPU6050_tockn.h>
#include <Wire.h>
// mpu
#include <LiquidCrystal_I2C.h>  //lcd i2c
LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu6050(Wire);
// ----------------------------------------- gps
#include <TinyGPS++.h> // gps
#include <SoftwareSerial.h>
TinyGPSPlus gps;
#define S_RX 8
#define S_TX 9
SoftwareSerial SoftSerial(S_RX, S_TX);
// -------------------------------------- rf
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte diachi[][6] = {"01234", "56789"}; 
//---------------------------------------- sim
#include <SoftwareSerial.h>
SoftwareSerial mySim(8,9); //Rx Tx
//----------------------------------------
const int relayPin = 8; //relay use with rf
int yellowled = 13;  // for speed
int redled = 12;     // for mpu
int buttonPin = 2; //button
int whistlePin = 11; //còi
int relay=3;//relay
void setup()

{
  Serial.begin(9600);
  //------------------------------------------
  lcd.init();
  lcd.backlight();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  SoftSerial.begin(9600);
  // -------------------------------------------
  pinMode(yellowled, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(relayPin, OUTPUT); 
  pinMode(buttonPin, INPUT);
  pinMode(whistlePin, INPUT);
  // ------------------------------------------rf
  // radio.begin();                     
  // radio.setAutoAck(1);              
  // radio.setDataRate(RF24_1MBPS);    // Tốc độ dữ liệu
  // radio.setChannel(10);               // Đặt kênh
  // radio.openReadingPipe(1,pipe);     
  // radio.startListening();            
  //-----------------------------------------
  mySim.begin(9600);//Sim

}
void loop() {
  getGps();

  if (gps.speed.kmph() >40) {
    digitalWrite(yellowled, 1);
  } else
    digitalWrite(yellowled, 0);

  mpu();
  // RfinBox();
  // button();
}

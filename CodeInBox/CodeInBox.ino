#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu6050(Wire);
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
#define S_RX 8
#define S_TX 9
SoftwareSerial SoftSerial(S_RX, S_TX);
int yellowled = 13;  // for speed
int redled = 12;     // for mpu
int relay = 8;
volatile byte relayState = LOW;
long lastDebounceTime = 0;  
long debounceDelay = 10000;

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
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode(PIRInterrupt, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIRInterrupt), detectMotion, RISING);
}

void loop() {
  getGps();

  if (gps.speed.kmph() >= 11) {
    digitalWrite(yellowled, 1);
  } else
    digitalWrite(yellowled, 0);

  mpu();
  RfinBox();
  RelayinBox();
}

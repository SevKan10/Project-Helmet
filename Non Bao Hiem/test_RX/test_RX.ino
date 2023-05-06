//--------------------------------------------------------RF
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte diachi[] = "01234";  
//--------------------------------------------------------RF
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
//--------------------------------------------------------Cấu trúc Data
struct package_receive{ int TX_Connect; };
package_receive data_receive;
//--------------------------------------------------------Khởi tạo ngoại vi
#define Buzze    2        //Còi
#define Power    3        //Kích nguồn
//--------------------------------------------------------Khởi tạo biến
unsigned long interrupt = 0; //Time chạy RF
unsigned long ping = 0;      //Độ trì hoãn
void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  if (radio.begin()) { Serial.println("NRF24L01 Start!"); } 
  radio.openReadingPipe(1, diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);

  pinMode(Buzze,  OUTPUT);
  pinMode(Power,  OUTPUT);

  lcd.setCursor(0,0); lcd.print("Device is ready!");
  delay(2000);
  lcd.clear();
}

void loop() 
{
 digitalWrite(Buzze, 0); digitalWrite(Power, 1);
 lcd.setCursor(0,0); lcd.print("Device Connected");
 NRF();
} 

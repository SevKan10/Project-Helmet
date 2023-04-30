 /*
 * VCC - 3.3v
 * GND - GND
 * CSN - 4
 * CE - 3
 * SCK - 13 mặc định SPI
 * MOSI - 11 SPI
 * MISO - 12 SPI0
 */

//--------------------------------------------------------LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
//--------------------------------------------------------SIM - EPROM
#include <SoftwareSerial.h>
#include <EEPROM.h>
SoftwareSerial simSerial(3, 2); 
//--------------------------------------------------------GPS 
#include <AltSoftSerial.h>
AltSoftSerial gpsSerial;
#include <TinyGPS++.h>
TinyGPSPlus gps;
//--------------------------------------------------------RF 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte diachi[][6] = {"01234", "56789"}; 
//--------------------------------------------------------Cấu trúc Data
struct package_send{ int TX_Connect; int SOS; };
package_send data_send;
struct package_receive{ int RX_Connect; int Call;};
package_receive data_receive;
//--------------------------------------------------------Hàm Reset
void(* resetFunc) (void) = 0;
//--------------------------------------------------------Khởi tạo biến
unsigned long interrupt; //Time chạy RF
unsigned long ping;      //Độ trì hoãn
String ADMIN;            //Số ĐT ADMIN
String MAP;              //Tọa độ trong EPPROM
String MAPS;             //Tọa độ 
int Mode = 0, flag = 6;  //Chế độ lấy tọa độ
float Lat, Lng;          //Tọa độ lấy trực tiếp 
String lt, lg;     

//--------------------------------------------------------Khởi tạo nút nhấn
#define SOS_btn  4        //Nút SOS
#define RS_Phone 5        //Nút xoá số đt ADMIN
#define RAIN     6        //Cảm biến mưa
#define Buzze    A0        //Còi

void setup() 
{
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  pinMode(SOS_btn,  INPUT_PULLUP);
  pinMode(RS_Phone, INPUT_PULLUP);
  pinMode(RAIN,     INPUT);
  pinMode(Buzze,    OUTPUT);

  simSerial.begin(9600);
  simSerial.println("AT+CMGF=1");   delay(500);  
  simSerial.println("AT+CNMI=2,2,0,0,0");   delay(500);
  simSerial.println("AT+CMGL=\"REC UNREAD\"");   delay(500); 
  for (int i = 0;  i < 12; ++i) { ADMIN  += char(EEPROM.read(i)); }
  for (int i = 15; i < 34; ++i) { MAP    += char(EEPROM.read(i)); }
  for (int i = 15; i < 23; ++i) { lt     += char(EEPROM.read(i)); }
  for (int i = 24; i < 34; ++i) { lg     += char(EEPROM.read(i)); }
  Serial.print(ADMIN); Serial.print(" | "); Serial.println(MAP);

  gpsSerial.begin(9600);
  
  if (radio.begin()) { Serial.println("NRF24L01 Start!"); } 
  radio.openWritingPipe(diachi[1]); 
  radio.openReadingPipe(1, diachi[0]);
  radio.setPALevel(RF24_PA_MIN); 
  radio.setDataRate(RF24_250KBPS);            

  if (ADMIN==0){
    lcd.setCursor(0,0); lcd.print(" Setting ADMIN  ");
    while (ADMIN==0) {Setup_ADMIN();}
  }

  lcd.setCursor(0,0); lcd.print("Device is ready!"); delay(1000); lcd.clear();
}

void loop() 
{
  Setup_MAP();
  Load_GPS();
  digitalWrite(Buzze, 0);
//-----------------------------------------------------------SOS  
  if(digitalRead(SOS_btn) == 0 || digitalRead(RAIN) == 0) 
  {
    lcd.clear(); lcd.setCursor(0,0); lcd.print("SOS!!!"); 
    Send_SOS();
  }
//-----------------------------------------------------------Reset ADMIN và chế độ lấy MAP
  if(digitalRead(RS_Phone)==0)
  {
    Mode = !Mode; 
    lcd.clear();
    while(digitalRead(RS_Phone)==0) 
    {
      flag--; delay(1000);
      lcd.setCursor(0,0); lcd.print("Reset ADMIN is: ");
      lcd.setCursor(0,1); lcd.print(flag); lcd.print("s");
      if(flag <= 0){ for (int i = 0; i < 12; ++i) {EEPROM.write(i, 0);} delay(500); resetFunc();} 
    }
     
    if(digitalRead(RS_Phone)==1){lcd.clear(); flag = 6;} 
  }
//-----------------------------------------------------------Load MAP  
  if(Mode==0)
  {   
      String mydata = mydata+Lat+","+Lng;
      MAPS = mydata;
      mydata = "";
      Serial.println(MAPS);
      lcd.setCursor(0,0); lcd.print("Lat: "); lcd.print(Lat, 6); lcd.print(".");
      lcd.setCursor(0,1); lcd.print("Lng: "); lcd.print(Lng, 6); lcd.print(".");
  }
  if(Mode==1)
  {    
      MAPS = MAP;
      Serial.println(MAPS);
      lcd.setCursor(0,0); lcd.print("Lat: "); lcd.print(lt);
      lcd.setCursor(0,1); lcd.print("Lng: "); lcd.print(lg);
  }
//-----------------------------------------------------------Load RF 
  if(millis() - interrupt >= 1000) {NRF(); interrupt = millis();} 
 
}

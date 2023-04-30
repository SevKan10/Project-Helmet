 /*
 * VCC - 3.3v
 * GND - GND
 * CSN - 4
 * CE - 3
 * SCK - 13 mặc định SPI
 * MOSI - 11 SPI
 * MISO - 12 SPI
 */
 
//--------------------------------------------------------RF
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte diachi[][6] = {"01234", "56789"};  
//--------------------------------------------------------Cấu trúc Data
struct package_send{ int RX_Connect; int Call; };
package_send data_send;
struct package_receive{ int TX_Connect; int SOS; };
package_receive data_receive;
//--------------------------------------------------------Khởi tạo ngoại vi
#define Call_btn     4        //Gọi về
#define Buzze    7        //Còi
//--------------------------------------------------------Khởi tạo biến
unsigned long interrupt; //Time chạy RF
unsigned long ping;      //Độ trì hoãn
void setup() 
{
  Serial.begin(9600);
  if (radio.begin()) { Serial.println("NRF24L01 Start!"); } 
  radio.openWritingPipe(diachi[0]); 
  radio.openReadingPipe(1, diachi[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);

  pinMode(Call_btn,     INPUT_PULLUP);
  pinMode(Buzze,    OUTPUT);
}

void loop() 
{
 digitalWrite(Buzze, 0);
 if(millis() - interrupt >= 1000) {NRF(); interrupt = millis();}
} 

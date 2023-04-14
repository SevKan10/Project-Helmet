

//ESP ĐỂ TRUYỀN DỮ LIỆU LÊN INTERNET
//ESP TO TRANSFER DATA ON THE INTERNET
#include <SoftwareSerial.h>
#define S_RX 2
#define S_TX 3
SoftwareSerial mySerial(S_RX, S_TX);  // RX, TX // CHÂN GIAO TIẾP VỚI ARDUINO - COMMUNICATION WITH ARDUINO
String myString;
char rdata;
int firstVal, secondVal, thirdVal, fourtVal;  // sensors
//----------------------------------------
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//KHỞI TẠO KẾT NỐI ĐẾN CLOUD MQTT - Initialize CONNECTION TO CLOUD MQTT
const char* ssid = "tháng 3";
const char* password = "jzbel.27";

WiFiClient espClient;
PubSubClient client(espClient);
String inData;
//----------------------------------------

//ID CỦA GOOGLE SHEET -  Initialize GOOGLE SHEET ID, TOKEN,...
#include <WiFiClientSecure.h>
const char* host = "script.google.com";
const int httpsPort = 443;
WiFiClientSecure clients;  //https
String GAS_ID = "AKfycbxtaloI2NlmjlvUlUMTFfI1nNmqXPKz2TLtMaOPYhJ5l2XyxJCCrwwfGaD5w4xDTZbe";
int value1, value2, value3, value4;
float longti, latti, speed;
//----------------------------------------
void setup() {
  Serial.begin(9600);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
  pinMode(BUILTIN_LED, OUTPUT);
  mySerial.begin(9600);
}

void loop() {
  longti=112;
  latti=123;
  speed=12;

  sendData(value1, value2, value3);  // HÀM NÀY ĐỂ GHI GIÁ TRỊ VÀO Spreadsheet - THIS FUNCTION TO WRITE VALUES into the Spreadsheet
  delay(100);
}

#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
#include <TinyGPS++.h>          
#include <SoftwareSerial.h>   
TinyGPSPlus gps;
#define S_RX    8                
#define S_TX    9      
SoftwareSerial SoftSerial(S_RX, S_TX);
boolean yellowled = 13;
boolean redled = 12;
boolean greenled = 11;
float initialLatitude = 10.029966;
float initialLongitude = 105.686610;
float latitude, longitude;

const float maxDistance = 30; // Tính theo hệ mét
// Lấy đèn để mô phỏng cho mp3

void getGps(float& latitude, float& longitude); // Make Virtual Fence

void setup()
 
 {
   Serial.begin(9600);
   SoftSerial.begin(9600); 
   Wire.begin();
   mpu6050.begin();
   mpu6050.calcGyroOffsets(true);
   pinMode(yellowled,OUTPUT);
   pinMode(redled,OUTPUT);
   pinMode(greenled,OUTPUT);
   yellowled = 0;
   redled = 0;
   greenled = 0;
 }

void loop()

 {
   // XỬ LÝ DỮ LIỆU CẢM BIẾN GPS
   boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 300;)
  {
    while (SoftSerial.available() > 0)
    {
      if (gps.encode(SoftSerial.read()))
      {
        newData = true;
      }
    }
  }
  // Tính vận tốc
  if (newData == true)
  {
    newData = false; 
    (gps.location.isValid() == 1);
    {
      Serial.print("Speed: ");
      Serial.print(gps.speed.kmph());
      Serial.println("Km/h"); 
      // In ra tốc độ 
      Serial.print("Sattlites: ");
      Serial.println(gps.satellites.value());
      // In ra số vệ tinh
     
    }
  if (gps.speed.kmph()>40) 
  {
      digitalWrite(yellowled,1);
  }
    // Nếu xe chạy trên 40km/h thì đèn vàng sẽ sáng
  }
  // XỬ LÝ GPS HÀNG RÀO ẢO
  getGps(latitude, longitude);
  float distance = getDistance(latitude, longitude, initialLatitude, initialLongitude);
  Serial.print("Latitude= "); Serial.println(latitude, 6);
  Serial.print("Lngitude= "); Serial.println(longitude, 6);
  Serial.print("initialLatitude= "); Serial.println(initialLatitude, 6);
  Serial.print("initialLngitude= "); Serial.println(initialLongitude, 6);
  Serial.print("current Distance= "); Serial.println(distance);
  if (distance > maxDistance)
  {
          digitalWrite(greenled,1);
  }
  else 
  {
          digitalWrite(greenled,0);
  }
  float getDistance(float flat1, float flon1, float flat2, float flon2) {

  // Variables
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;

  // Calculations
  diflat  = radians(flat2-flat1);
  flat1 = radians(flat1);
  flat2 = radians(flat2);
  diflon = radians((flon2)-(flon1));

  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2 = cos(flat1);
  dist_calc2*=cos(flat2);
  dist_calc2*=sin(diflon/2.0);
  dist_calc2*=sin(diflon/2.0);
  dist_calc +=dist_calc2;

  dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));
  
  dist_calc*=6371000.0; //Converting to meters

  return dist_calc;
}
void getGps(float& latitude, float& longitude)
{
  // Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;){
    while (gps.available()){
      if (gps.encode(neogps.read())){
        newData = true;
        break;
      }
    }
  }
  
  if (newData) //If newData is true
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    newData = false;
  }
  else {
    Serial.println("No GPS data is available");
    latitude = 0;
    longitude = 0;
  }
}
//*************************************************
    // XỬ LÝ DỮ LIỆU MPU6050
     mpu6050.update();
     float x= mpu6050.getAccX();
     float y = mpu6050.getAccY();
     float z = mpu6050.getAccZ();
     Serial.println("Value MPU6056");
     Serial.print("x: "); Serial.print(x);
     Serial.print("\ty: "); Serial.print(y);
     Serial.print("\tz: "); Serial.println(z);
     delay(200);
     // Lấy giá trị y để xác định
    if (y>0.90)
     {
      Serial.println("xe bi nga ");
      digitalWrite(redled,1);
     }
    // Nếu y có giá trị trên 90 thì xe ngã khi đó đèn đỏ sáng 
//**************************************************
 }
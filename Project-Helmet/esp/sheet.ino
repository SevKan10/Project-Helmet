// HÀM ĐỂ GHI DỮ LIỆU VÀO Spreadsheet
// FUNCTION TO WRITE DATA to Spreadsheet
void sendData(float longti, float latti, float speed) 
{
  if (!clients.connect(host, httpsPort)) { return; }

  String longti_I = String(longti);
  String latti_I = String(latti);
  String speed_P = String(speed);
  
  String url = "/macros/s/" + GAS_ID + "/exec?value1=" + longti_I + "&value2=" + latti_I  + "&value3=" + speed_P;
  clients.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
}
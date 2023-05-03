void SIM()
{
   if (mySerial.available()>0)
 Serial.write(mySerial.read());

}
      void SendMessage()//Gửi SMS
      {
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(1000);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+84866207887\"\r"); // Replace x with mobile number
        delay(1000);
        mySerial.println("Help me");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(1000);
      }

      void MakeCall()//Gọi
      {
        mySerial.println("ATD+84866207887;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
        Serial.println("Calling  "); // print response over serial port
        delay(1000);
      }
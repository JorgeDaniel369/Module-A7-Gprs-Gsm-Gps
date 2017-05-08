void GPS()
{
  Serial.println("GPS Activation..");
  SendData("AT",2000,S1debug);
  delay(100);
  SendData("AT+GPSRD=1",2000,S1debug);
  delay(100);
  SendData("AT+GPS=1",2000,S1debug);
  delay(100);
  x=1;
}



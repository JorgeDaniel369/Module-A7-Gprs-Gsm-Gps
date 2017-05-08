void Encode()
{
   Serial.println("HIJO SOLO ME IMPRIMO UNA VEZ");
  gps.encode(shieldSerial.read());
  while(shieldSerial.available()>0)
  if(gps.encode(shieldSerial.read()))

  if (gps.time.isValid()==1)
  {
    gps_latitude=gps.time.hour();
    gps_longitude=gps.time.second();
    gps_altitude=gps.time.minute();
    //gps_satelite=gps.satellites.value();
    
  }
  
  smartdelay(800);
  if (millis()>5000 && gps.charsProcessed()<10)
  {
    Serial.println(F("NO Detected GPS.."));
    while(true);
  }
}


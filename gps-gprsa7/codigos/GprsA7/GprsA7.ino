/* The Monitor Car Controll
 * Created by Island
 * Modified by Ing. Jorge Daniel Gutierrez Felix
 * Date: 22/04/2017
 */
 // el problema que tengo hasta ahorita es la interpretacion entros los dos serial's ya que en leonardo son totalmente independientes uno de los otros. analizar el codigo :D
 #include <TinyGPS++.h> 
 #include <SoftwareSerial.h> \\SE EJECUTA LA LIBRERIA SOFTSERIAL
 #define rx 7 //SE DEFINE EL PIN 7 COMO RX
 #define tx 8 //SE DEFINE EL PIN 8 COMO TX
 SoftwareSerial shieldSerial(rx, tx);
 TinyGPSPlus gps;
 byte powerkey =3;
 //DECLARATION GPS VARIABLES//
 byte gps_satelite,gps_days,gps_moths,gps_seconds,gps_minutes,gps_hour;
 double gps_longitude,gps_latitude,gps_altitude;
 int gps_year;
 byte x=0;

#define S1debug true
#define S_debug true

void setup()
{
  //SE INICIALIZAN LOS PUERTOS UART
  digitalWrite(powerkey, LOW);
  shieldSerial.begin(115200);   // the GPRS baud rate   
  Serial.begin(115200);    // THE RATE OF GPRS BAUD RATE 
  pinMode(powerkey, OUTPUT);
  power();
}
void power(void)
{
  Serial.println("estamos Prendiendo el shield");
  digitalWrite(powerkey, HIGH);
  delay(2000);
  digitalWrite(powerkey, LOW);
}

 
void loop()
{ 
  if (x==1)
  {
    //Encode();  
  }
  //Serial.println("loop");
/*
 * After start up the program, you can using terminal to connect the serial of gprs shield,
 * If you input 't' in the terminal, the program will execute SendTextMessage(), it will show how to send a sms message,
 * If input 'd' in the terminal, it will execute DialVoiceCall(), etc.
 */
  delay(500);
  if (Serial.available())
  {
    
    switch(Serial.read())
    { 
     case 't':
       GPS();
       
       break;
     case 'd':
       //DialVoiceCall();
       break;
     case 'h':
       //SubmitHttpRequest();
       break;
     case 'q':
       //GetSignalQuality();
       break;
   } 
  }
   RecData();
   
}
 
/*
 * SendTextMessage()
 * This function is to send a sms message
 */
//void SendTextMessage()
//{ 
//  Serial.println("Entro a los mensajes");
//  SendData("",2000,S1debug);
//  SendData("AT+CMGF=1",2000,S1debug);//Because we want to send the SMS in text mode
//  delay(100);
//  SendData("AT+CMGS=+526681629365",2000,S1debug);//send sms message, be careful need to add a country code before the cellphone number
//  delay(100);
//  SendData("GSM test message!",2000,S1debug);//the content of the message
//  delay(100);
//  shieldSerial.println((char)26);//the ASCII code of the ctrl+z is 26
//  delay(100);
//}
// 
///*
// * DialVoiceCall
// * This function is to dial a voice call
// */
//void DialVoiceCall()
//{
//   SendData("AT+SNFS=0",2000,S1debug);
//   delay(100);
//   SendData("ATD6681629365",2000,S1debug);// "ATD+86137xxxxxxxx"dial the number
//   delay(100);
//}
// 
///*
// * SubmitHttpRequest()
// * This function is submit a HTTP request
// * attention:the time of delay is very important, it must be set enough 
// */
//void SubmitHttpRequest(){
//   SendData("AT+CREG?",1000,S1debug); //Query network registration
//   delay(100);
//   
//   SendData("AT+CGATT=1",2000,S1debug);
//   delay(100);
// 
//   SendData("AT+CGDCONT=1,\"IP\",\"CMNET\"",2000,S1debug);//setting PDP parameter 
//   delay(100);
// 
//   SendData("AT+CGACT=1,1",2000,S1debug); //Activate PDP, open Internet service
//   delay(100);
// 
//   SendData("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80",5000,S1debug); //Establish TCP connection
//   delay(100);
// 
//   SendData("AT+CIPSEND=5,\"12345\"",2000,S1debug); //Send string "12345" 
//   delay(100); 
//   
//   SendData("AT+CIPCLOSE",2000,S1debug);     //Close TCP
//   delay(100); 
//}
//
//void GetSignalQuality(){
//     Serial_Print("Getting the sinal quality...",S_debug);
//     SendData("AT+CSQ",1000,S1debug);
//     Serial_Print("Tips:+CSQ: XX,QQ : It means the Signal Quality poorly when the XX is '99'!",S_debug);
//}
//
static void smartdelay(unsigned long ms)
{
  unsigned long start=millis();
  do
  {
    while(shieldSerial.available())
      gps.encode(shieldSerial.read());
  }while (millis()-start<ms);
}
void SendData(String command, const int timeout, boolean debug) // fUNCION ("COMANDOS AT, DELAY, TRUE)
{
    String response = "";      //SE DECLARA TIPO CADENA VARIABLE DE NOMBRE RESPONSE
    shieldSerial.println(command);  //IMPRIME POR EL PUERTO EL COMANDO AT
    delay(5);                       //ESPERA 5 MS 
    if(debug)              // SI ES TRUE? ENTONCES
    {
    long int time = millis();   //VARIABLE TIME SE LE ACIGNA LA FUNCION MILLIS()
    Serial.println(time);
    while( (time+timeout) > millis()) //SI TIME + EL DELAY ENTRE COMANDOS ES MAYOR QUE MILIS
    {
      while(shieldSerial.available()) //SI ESTA HABILITADO EL SOFTSERIAL
      {       
        response += char(shieldSerial.read()); //RESPONSE ES IGUAL A LO QUE LEE EL SOFTWARE SERIAL
      }  
    }    
      Serial.print(response); //SE IMPRIME EN EL SERIAL LOS DATOS LEIDOS
     }    
}
//
void Serial_Print(String data, boolean debug) // STRING DATA, TRUE
{
  if(debug)        //TRUE
  {
    Serial.println(data); //IMPRIME EL VALOR DE DATA
  }
}
//
void RecData()
{
    String response = "";    
    while(shieldSerial.available())
    {       
        response += char(shieldSerial.read());
        //Serial.println(response);
        //Prints();
      }    
      Serial.print(response);  
}


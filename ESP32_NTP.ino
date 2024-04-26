#include <NTPClient.h>
// change next line to use with another board/shield
//#include <ESP8266WiFi.h>
#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "Wokwi-GUEST";
const char *password = "";

#define HORA_MEDICACAO_1  10
#define HORA_MEDICACAO_2  11


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -10800, 60000);

String atual, anterior = "";

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password, 6);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  atual = timeClient.getFormattedTime();

  if( atual != anterior )
  {
    anterior = atual;
    Serial.println(atual);

    if(timeClient.getMinutes() == HORA_MEDICACAO_1)
    {
      if( (timeClient.getSeconds() < 10) && (timeClient.getSeconds() > 0) )
      {
        Serial.println("beep1");
      }
    }

    if(timeClient.getMinutes() == HORA_MEDICACAO_2)
    {
      if( (timeClient.getSeconds() < 10) && (timeClient.getSeconds() > 0) )
      {
        Serial.println("beep2");
      }
    }
  }
 
//  Serial.println(timeClient.getHours());
//  Serial.println(timeClient.getMinutes());
//  Serial.println(timeClient.getSeconds());
//  
  delay(1000);
}

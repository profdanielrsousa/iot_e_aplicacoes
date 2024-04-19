/* DÉCIMO PROGRAMA (ESP32 e 74HC595)
   DANIEL RODRIGUES DE SOUSA 19/04/2024 */ 

#include <SPI.h>                          //Biblioteca para SPI

#define SS  5

unsigned char mestre_envia = 0;

void setup (void)
{
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);                 //pino SS em 1
  SPI.setClockDivider(SPI_CLOCK_DIV2);    //configura clock @ 8MHz
  SPI.begin();                            //inicializa comunicação SPI
}

void loop(void)
{
  mestre_envia++;
  SPI.transfer(mestre_envia);             //envia dados ao escravo
  digitalWrite(SS, LOW);                  // pulso de SS
  delayMicroseconds(1);
  digitalWrite(SS, HIGH);
  
  delay(1000);
}
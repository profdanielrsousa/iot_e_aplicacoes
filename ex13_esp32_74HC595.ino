/* DÉCIMO TERCEIRO PROGRAMA (ESP32 e 74HC595)
   DANIEL RODRIGUES DE SOUSA 19/04/2024
   PROJETO: https://wokwi.com/projects/395608422656972801 */ 

#include <SPI.h>  // Biblioteca para SPI

#define SS  5     // Define o pino 5 como SS (Slave Select)

unsigned char mestre_envia = 0; // Variável para armazenar o dado a ser enviado pelo mestre

void setup (void)
{
  pinMode(SS, OUTPUT);                  // Configura o pino SS como saída
  digitalWrite(SS, HIGH);               // Define o pino SS em nível alto
  SPI.setClockDivider(SPI_CLOCK_DIV2);  // Configura o clock SPI para 8MHz
  SPI.begin();                          // Inicializa a comunicação SPI
}

void loop(void)
{
  mestre_envia++;             // Incrementa o valor a ser enviado
  SPI.transfer(mestre_envia); // Envia o dado ao escravo via SPI
  
  digitalWrite(SS, LOW);      // Pulso no pino SS para iniciar a comunicação
  delayMicroseconds(1);       // Pequeno atraso para garantir a comunicação
  digitalWrite(SS, HIGH);     // Define o pino SS em nível alto novamente
  
  delay(1000);  // Aguarda 1 segundo antes de enviar o próximo dado
}

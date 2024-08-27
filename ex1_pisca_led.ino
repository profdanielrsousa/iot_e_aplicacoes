/* PRIMEIRO PROGRAMA (PISCA LED)
   DANIEL RODRIGUES DE SOUSA 22/09/2021 
   PROJETO: https://wokwi.com/projects/407042745702298625 */

#define	LED	13 //pino onde está ligado o LED

void setup()
{
  pinMode(LED, OUTPUT); //direção do pino (saída)
}

void loop()
{
  digitalWrite(LED, HIGH);//pino em nível alto (5 Volts)
  delay(1000);            //delay de 1 segundo  
  digitalWrite(LED, LOW); //coloca pino em nível baixo (GND)
  delay(1000);            //delay de 1 segundo
}

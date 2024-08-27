/* SEGUNDO PROGRAMA (PISCA LED MODIFICADO)
   DANIEL RODRIGUES DE SOUSA 26/02/2024
   PROJETO: https://wokwi.com/projects/407333186071195649 */

#define	LED	13 //pino onde está ligado o LED

void setup()
{
  pinMode(LED, OUTPUT); //direção do pino (saída)
}

void loop()
{
  digitalWrite(LED,!digitalRead(LED));	//lê o estado atual do pino e troca o estado
  delay(1000);            		          //delay de 1 segundo  
}

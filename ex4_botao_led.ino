/* QUARTO PROGRAMA (BOTÃO E LED)
   DANIEL RODRIGUES DE SOUSA 02/03/2024 
   PROJETO: https://wokwi.com/projects/407042775519607809 */

#define LED   8 // Define a constante LED no pino 8
#define BOTAO 9 // Define a constante BOTAO no pino 9

void setup()
{
  // Configura as portas de saída e entrada para o LED e botão respectivamente
  pinMode(LED, OUTPUT);   // Define o pino do LED como saída
  pinMode(BOTAO, INPUT);  // Define o pino do botão como entrada
}

void loop()
{
  if(digitalRead(BOTAO) == 0) // Verifica se o botão está pressionado (0) ou não (1)
  {
    digitalWrite(LED, HIGH);  // Se estiver pressionado, acende o LED
  }
  else
  {
    digitalWrite(LED, LOW);   // Se não estiver pressionado, apaga o LED
  }
}

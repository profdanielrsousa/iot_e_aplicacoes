/* QUARTO PROGRAMA (BOTÃO E LED)
   DANIEL RODRIGUES DE SOUSA 02/03/2024 */

#define LED		8
#define BOTAO	9

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BOTAO, INPUT);
}

void loop()
{
  if(digitalRead(BOTAO) == 0)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}
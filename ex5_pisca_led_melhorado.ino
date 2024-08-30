/* QUINTO PROGRAMA (PISCA-LED MELHORADO)
   DANIEL RODRIGUES DE SOUSA 08/03/2024
   PROJETO: https://wokwi.com/projects/407648914867887105 */

#define LED     11  //definição do LED
#define POT     A0  //definição do potenciômetro

unsigned int tempo = 0;

void setup()
{
  pinMode(LED, OUTPUT);
}
void loop()
{
  tempo = analogRead(POT);      //lê potenciômetro
  digitalWrite(LED, !digitalRead(LED));
  delay(tempo);
}
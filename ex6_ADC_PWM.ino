/* SEXTO PROGRAMA (MODULAÇÃO POR LARGURA DE PULSO - PWM)
   DANIEL RODRIGUES DE SOUSA 08/03/2024
   PROJETO: https://wokwi.com/projects/407649684177770497 */

#define LED 11  //definição do LED
#define POT A0  //definição do potenciômetro

unsigned int brilho;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  brilho = analogRead(POT); //lê potenciômetro
  brilho = map(brilho, 0, 1023, 0, 255);
  Serial.println(brilho);   //envia pela serial
  analogWrite(LED, brilho);
  delay(100);
}
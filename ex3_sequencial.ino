/* TERCEIRO PROGRAMA (SEQUÊNCIAL "SUPER MÁQUINA")
   DANIEL RODRIGUES DE SOUSA 02/03/2024
   PROJETO: https://wokwi.com/projects/407332951625252865 */

#define LED13	13
#define LED12	12
#define LED11	11
#define LED10	10
#define LED9	9
#define LED8	8

void setup()
{
  pinMode(LED13, OUTPUT);
  pinMode(LED12, OUTPUT);
  pinMode(LED11, OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(LED8, OUTPUT);
}

void loop()
{
  digitalWrite(LED13, LOW);
  digitalWrite(LED12, HIGH);
  delay(100);

  digitalWrite(LED12, LOW);
  digitalWrite(LED11, HIGH);
  delay(100);

  digitalWrite(LED11, LOW);
  digitalWrite(LED10, HIGH);
  delay(100);

  digitalWrite(LED10, LOW);
  digitalWrite(LED9, HIGH);
  delay(100);

  digitalWrite(LED9, LOW);
  digitalWrite(LED8, HIGH);
  delay(100);

  digitalWrite(LED8, LOW);
  digitalWrite(LED9, HIGH);
  delay(100);

  digitalWrite(LED9, LOW);
  digitalWrite(LED10, HIGH);
  delay(100);

  digitalWrite(LED10, LOW);
  digitalWrite(LED11, HIGH);
  delay(100);

  digitalWrite(LED11, LOW);
  digitalWrite(LED12, HIGH);
  delay(100);

  digitalWrite(LED12, LOW);
  digitalWrite(LED13, HIGH);
  delay(100);
}

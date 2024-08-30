/* SÉTIMO PROGRAMA (SENSOR LDR)
   DANIEL RODRIGUES DE SOUSA 08/03/2024
   PROJETO: https://wokwi.com/projects/407650215539512321 */  
   
int ent_analogica;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  ent_analogica = analogRead(A0);
  Serial.println(ent_analogica);
  delay(250);
}
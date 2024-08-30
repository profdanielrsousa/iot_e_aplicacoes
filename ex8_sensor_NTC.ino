/* OITAVO PROGRAMA (SENSOR DE TEMPERATURA NTC)
   REFERÊNCIA: https://www.makerhero.com/blog/termistor-ntc-arduino/
   DANIEL RODRIGUES DE SOUSA 08/03/2024 */

#define pinTermistor  A0

// Parâmetros do termistor
#define beta  3600.0
#define r0    10000.0
#define t0    273.0 + 25.0
#define rx    r0 * exp(-beta/t0)
 
// Parâmetros do circuito
#define vcc   5.0
#define R     10000.0
 
// Numero de amostras na leitura
#define nAmostras 5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Le o sensor algumas vezes
  int soma = 0;
  for(int i = 0; i < nAmostras; i++)
  {
    soma += analogRead(pinTermistor);
    delay(10);
  }
 
  // Determina a resistência do termistor
  double v = (vcc*soma)/(nAmostras*1024.0);
  double rt = (vcc*R)/v - R;
 
  // Calcula a temperatura
  double t = beta / log(rt/rx);
  Serial.println(t-273.0);
  delay(100);
}
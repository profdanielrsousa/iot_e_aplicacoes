/* OITAVO PROGRAMA (SENSOR DE TEMPERATURA NTC - MÓDULO IDUINO)
   REFERÊNCIA:  https://docs.wokwi.com/parts/wokwi-ntc-temperature-sensor
                https://www.openplatform.cc/index.php/home/index/details/apiid/128
   DANIEL RODRIGUES DE SOUSA 30/08/2024 
   PROJETO: https://wokwi.com/projects/407650698704509953 */

#define pinTermistor  A0      // Pino analógico
#define beta          3950.0  // Parâmetros do termistor

int analogValue;
float temperatura;

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  analogValue = analogRead(pinTermistor);

  // Calcula a temperatura
  temperatura = 1 / (log(1 / (1023. / analogValue - 1)) / beta + 1.0 / 298.15) - 273.15;
  Serial.println(temperatura);
  delay(100);
}
/* DÉCIMO OITAVO PROGRAMA (IoT COM ARDUINO IOT, ESP32 E LEDS)
   DANIEL RODRIGUES DE SOUSA 10/05/2024 */ 

/* 
  Sketch gerado pelo Thing "Sem título" do Arduino IoT Cloud 
  https://create.arduino.cc/cloud/things/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 

  Variáveis do Arduino IoT Cloud descritas

  As seguintes variáveis são automaticamente geradas e atualizadas quando houver alterações no Thing

  bool led_blue;
  bool led_green;
  bool led_red;

  As variáveis marcadas como LER/ESCREVER na nuvem do Thing também terão funções
  que serão chamadas quando seus valores forem modificados a partir da Dashboard.
  Essas funções são geradas com o Thing e adicionadas ao final desse sketch.
*/

#include "ex18_esp32_ARDUINO_IOT_LED_RGB.h"

#define LED_RED   5
#define LED_GREEN 17
#define LED_BLUE  16

void setup() {
  // Inicialize serial e aguarde a porta abrir:
  Serial.begin(115200);
  // Este atraso permite esperar por um Monitor de Série sem bloquear se nenhum for encontrado
  delay(1000); 

  // Definido em thingProperties.h
  initProperties();

  // Conecte-se ao Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
    A seguinte função permite obter mais informações relacionadas ao estado da rede e conexão do IoT Cloud e erros.
    O número maior, mais detalhes você terá. 
    O padrão é 0 (apenas erros).
    Máximo é 4
 */  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  ArduinoCloud.update();
   // Seu código aqui 
  
  
}

/*
  Como LedRed é uma variável READ_WRITE, onLedRedChange() será executada a cada vez que um novo valor for recebido da IoT Cloud.
*/

void onLedRedChange()  {
  // Adicione seu código aqui para agir sobre o LedRed
  digitalWrite(LED_RED, led_red);
}

/*
  Como LedGreen é uma variável READ_WRITE, onLedGreenChange() será executada a cada vez que um novo valor for recebido da IoT Cloud.
*/

void onLedGreenChange()  {
  // Adicione seu código aqui para agir sobre o LedGreen
  digitalWrite(LED_GREEN, led_green);
}

/*
  Como LedBlue é uma variável READ_WRITE, onLedBlueChange() será executada a cada vez que um novo valor for recebido da IoT Cloud.
*/

void onLedBlueChange()  {
  // Adicione seu código aqui para agir sobre o LedBlue
  digitalWrite(LED_BLUE, led_blue);
}

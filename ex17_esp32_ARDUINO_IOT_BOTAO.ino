/* DÉCIMO SÉTIMO PROGRAMA (IoT COM ARDUINO IOT, ESP32 E BOTÕES)
   DANIEL RODRIGUES DE SOUSA 10/05/2024 */ 

/* 
  Sketch gerado pelo Thing "Sem título" do Arduino IoT Cloud 
  https://create.arduino.cc/cloud/things/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 

  Variáveis de descrição do Arduino IoT Cloud

  As seguintes variáveis são automaticamente geradas e atualizadas quando houver alterações no Thing

  bool botao1;
  bool botao2;
  bool botao3;

  As variáveis marcadas como LER/ESCREVER na nuvem serão também associadas a funções
  que seriam chamadas quando seus valores forem modificados do painel de controle.
  Essas funções são geradas com o Thing e adicionadas ao final desse sketch.
*/

#include "ex17_esp32_ARDUINO_IOT_BOTAO.h"

#define BOTAO_1   5  
#define BOTAO_2   17 
#define BOTAO_3   16 

void setup() {
  // Inicialize a comunicação serial e aguarde a porta abrir:
  Serial.begin(9600);
  // Este delay permite que você espere um monitor de série sem bloquear se nenhum for encontrado
  delay(1000); 

  // Definido em ex16_esp32_ARDUINO_IOT_BOTAO.h
  initProperties();

  // Conecte-se ao Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /* 
    A seguinte função permite que você obtenha mais informações
    relacionadas ao estado da rede e da conexão com o nuvem, bem como erros.
    O número maior fornece informações mais detalhadas. O padrão é 0 (apenas erros).
    Máximo é 4
  */

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(BOTAO_1, INPUT);
  pinMode(BOTAO_2, INPUT);
  pinMode(BOTAO_3, INPUT);
}

void loop() {
  ArduinoCloud.update();
  
  // Seu código aqui 
  botao1 = digitalRead(BOTAO_1);
  botao2 = digitalRead(BOTAO_2);
  botao3 = digitalRead(BOTAO_3);  
}

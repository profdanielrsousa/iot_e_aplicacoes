/* NONO PROGRAMA (SENSOR PIR E MÓDULO RELÉ)
   DANIEL RODRIGUES DE SOUSA 06/09/2024 
   PROJETO: https://wokwi.com/projects/408285980365521921 */

#define LED_DEBUG 13 // Definição do pino do LED de debug
#define RELE      8  // Definição do pino do relé
#define PIR       9  // Definição do pino do sensor PIR

// Variáveis para temporização
unsigned long int tempo_atual;   
unsigned long int tempo_500ms;

void setup()
{
  // Configuração dos pinos
  pinMode(LED_DEBUG, OUTPUT); // Configura o pino do LED de debug como saída
  pinMode(RELE, OUTPUT);      // Configura o pino do relé como saída
  pinMode(PIR, INPUT);        // Configura o pino do sensor PIR como entrada

  // Inicialização do temporizador usando o método millis()
  tempo_500ms = millis();
}

void loop()
{
  // Atualização do tempo atual
  tempo_atual = millis();

  // Verificação do temporizador a cada 500ms
  if((tempo_atual - tempo_500ms) >= 500) 
  {
    // Recarrega o temporizador
    tempo_500ms = millis();

    // Alterna o estado do LED de debug
    digitalWrite(LED_DEBUG, !digitalRead(LED_DEBUG)); 
  }

  // Controla o relé baseado na leitura do sensor PIR
  digitalWrite(RELE, digitalRead(PIR));
}

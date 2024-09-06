/* DÉCIMO PROGRAMA (SENSOR ULTRASSÔNICO HC-SR04)
   DANIEL RODRIGUES DE SOUSA 06/09/2024 
   PROJETO: https://wokwi.com/projects/408216424033571841 */

#define VCC_FAKE  A0 // Definição do pino para simulação de VCC (alimentação) 
#define ECHO      A2 // Definição do pino ECHO do sensor ultrassônico
#define TRIGGER   A1 // Definição do pino TRIGGER do sensor ultrassônico
#define GND_FAKE  A3 // Definição do pino para simulação de GND (terra)

#define VERDE     3  // Definição do pino do LED verde
#define VERMELHO  2  // Definição do pino do LED vermelho

// Definição de unidade de medida: cm ou pol (polegadas)
#define MEDIDA_CM

// Variáveis para temporização
unsigned long int tempo_atual;   
unsigned long int tempo_500ms;
float distancia;

void setup()
{
  // Configuração dos pinos de saída
  pinMode(VERDE, OUTPUT);
  pinMode(VERMELHO, OUTPUT);

  // Configuração dos pinos do sensor ultrassônico
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(VCC_FAKE, OUTPUT);
  pinMode(GND_FAKE, OUTPUT);
  
  // Inicialização dos pinos de alimentação simulada
  digitalWrite(GND_FAKE, LOW);
  digitalWrite(VCC_FAKE, HIGH);
  delay(500);
  
  // Inicialização da comunicação serial
  Serial.begin(9600);

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

    // Leitura da distância do sensor ultrassônico
    distancia = le_sensor();
    Serial.print(distancia);
    
    #ifdef  MEDIDA_CM
      Serial.println(" cm");  // Exibe a distância em centímetros
    #else
      Serial.println(" pol"); // Exibe a distância em polegadas
    #endif
  }
  
  // Controle dos LEDs baseado na distância medida
  if(distancia < 100)
  {
    digitalWrite(VERMELHO, LOW); // Desliga o LED vermelho
    digitalWrite(VERDE, HIGH);   // Liga o LED verde
  }
  else
  {
    digitalWrite(VERDE, LOW);     // Desliga o LED verde
    digitalWrite(VERMELHO, HIGH); // Liga o LED vermelho   
  }
}

// Função para leitura do sensor ultrassônico
float le_sensor(void)
{
  long duracao;
   
  // Gera um pulso no pino TRIGGER para iniciar a leitura do sensor
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  duracao = pulseIn(ECHO, HIGH);

  // Converte a duração do pulso em distância
  #ifdef  MEDIDA_CM
    return((float)duracao*0.034/2); // Retorna a distância em centímetros
  #else
    return((float)duracao*0.0133/2);// Retorna a distância em polegadas
  #endif
}

/* DÉCIMO PRIMEIRO PROGRAMA (SENSOR ULTRASSONICO HC-SR04 E SERVOMOTOR)
   DANIEL RODRIGUES DE SOUSA 05/09/2024 
   PROJETO: https://wokwi.com/projects/408197896407363585 */

#include <Servo.h>

#define ECHO      12 // Definição do pino ECHO do sensor ultrassônico
#define TRIGGER   13 // Definição do pino TRIGGER do sensor ultrassônico
#define SERVO     3  // Definição do pino do servo motor

// Definição da unidade de medida: cm ou pol (polegadas)
#define MEDIDA_CM

Servo meuServo;   // Cria um objeto Servo
float distancia;  // Variável para armazenar a distância medida

void setup()
{
  // Configuração dos pinos do sensor ultrassônico
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
  // Configuração do servo motor
  meuServo.attach(SERVO);
  meuServo.write(0); // Servo na posição inicial

  // Inicialização da comunicação serial
  Serial.begin(9600);
}

void loop() 
{
  // Calcula a distância
  distancia = le_sensor();
  
  // Exibe a distância medida no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);

  #ifdef  MEDIDA_CM
    Serial.println(" cm");  // Exibe a distância em centímetros
  #else
    Serial.println(" pol"); // Exibe a distância em polegadas
  #endif  
 
  // Verifica a distância e move o servo motor
  #ifdef  MEDIDA_CM
    if(distancia <= 50)     // Se a distância for menor ou igual a 50 cm
  #else
    if(distancia <= 19.685) // Se a distância for menor ou igual a 19.685 polegadas
  #endif 
  {
    meuServo.write(90); // Move o servo para a posição de 90 graus
  } 
  else 
  {
    meuServo.write(0);  // Move o servo para a posição inicial de 0 graus
  }

  delay(500); // Aguarda 500 ms antes de realizar a próxima leitura
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
  
  // Mede a duração do pulso no pino ECHO
  duracao = pulseIn(ECHO, HIGH);

  // Converte a duração do pulso em distância
  #ifdef  MEDIDA_CM
    return((float)duracao*0.034/2); // Retorna a distância em centímetros
  #else
    return((float)duracao*0.0133/2);// Retorna a distância em polegadas
  #endif
}

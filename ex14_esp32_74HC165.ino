/* DÉCIMO QUARTO PROGRAMA (ESP32 e 74HC165 - software SPI)
   DANIEL RODRIGUES DE SOUSA 26/09/2024
   PROJETO: https://wokwi.com/projects/410118912149818369 */ 

#define SS    5   // Define o pino 5 como SS (Slave Select)
#define CLK   18  // Define o pino 18 como CLK (Clock)
#define MISO  19  // Define o pino 19 como MISO (Master In Slave Out)

unsigned char mestre_recebe;  // Variável para armazenar o dado recebido pelo mestre

void setup (void)
{
    pinMode(SS, OUTPUT);  // Define o pino SS como saída
    pinMode(CLK, OUTPUT); // Define o pino CLK como saída
    pinMode(MISO, INPUT); // Define o pino MISO como entrada

    digitalWrite(SS, HIGH); // Pino SS inicialmente em nível alto
    Serial.begin(9600);  // Inicia a comunicação serial com a taxa de 9600 bps
}

void loop(void)
{
    digitalWrite(SS, LOW);  // Pino SS em nível baixo (pulso de SS)
    delayMicroseconds(1);   // Atraso de 1 microssegundo
    digitalWrite(SS, HIGH); // Pino SS novamente em nível alto
    
    mestre_recebe = le_sw_SPI();  // Chama a função para ler dados via SPI

    Serial.println(mestre_recebe);// Imprime o dado recebido na serial

    delay(1000);  // Atraso de 1 segundo
}

unsigned char le_sw_SPI(void)
{
  byte dado = 0x00; // Variável para armazenar o dado lido
  // O primeiro bit lido é o bit mais significativo (entrada D7 do 74HC165).
  for(int i = 7; i >= 0; i--)
  {
    if(digitalRead(MISO)) // Lê o valor do pino MISO
    {
      bitSet(dado, i);    // Define o bit correspondente em 'dado' se MISO estiver alto
    }
    digitalWrite(CLK, HIGH);  // Define o pino CLK em nível alto
    delayMicroseconds(100);   // Atraso de 100 microssegundos
    digitalWrite(CLK, LOW);   // Define o pino CLK em nível baixo
  }
  return(dado); // Retorna o dado lido
}

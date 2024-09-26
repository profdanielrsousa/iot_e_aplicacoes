/* DÉCIMO SEGUNDO PROGRAMA (ENVIO DE DADOS PARA O PYTHON VIA SERIAL)
   REFERÊNCIA: https://github.com/WaveShapePlay/Arduino_RealTimePlot/tree/master
   DANIEL RODRIGUES DE SOUSA 15/03/2024 */

#define POT A0  // Define o pino analógico A0 como POT

int dado = 0;           // Variável para armazenar o valor lido do potenciômetro
char caractere;         // Variável para armazenar o caractere lido da serial

void setup()
{
  Serial.begin(9600);   // Inicia a comunicação serial com a taxa de 9600 bps
}

void loop()
{
  if(Serial.available() > 0)
  { 
      caractere = Serial.read();  // Lê o caractere da entrada serial
      if(caractere == 'g')
      { // Se o caractere lido for 'g'
        dado = analogRead(POT);   // Lê o valor analógico do pino POT
        Serial.println(dado);     // Envia o valor lido para a serial
      } // Fim da verificação do caractere 'g'
    } // Fim da verificação de dados disponíveis na serial
} // Fim do loop

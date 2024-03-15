/* NONO PROGRAMA (ENVIO DE DADOS PARA O PYTHON VIA SERIAL)
   REFERÊNCIA: https://github.com/WaveShapePlay/Arduino_RealTimePlot/tree/master
   DANIEL RODRIGUES DE SOUSA 15/03/2024 */

#define POT A0

int dado = 0;           
char caractere;

void setup()
{
  Serial.begin(9600);                        // Inicia a comunicação serial
}

void loop()
{
  if(Serial.available() > 0)
  { 
      caractere = Serial.read();  // Lê a entrada do usuário
      if(caractere == 'g')
      { // Se recebermos o valor esperado
        dado = analogRead(POT);   // Lê o pino de entrada
        Serial.println(dado);     // Imprime o valor lido
      } // Se a entrada do usuário for 'g'
    } // Se houver dados disponíveis na serial
} // Fim do Loop

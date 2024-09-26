/* DÉCIMO QUINTO PROGRAMA (ESP32 e LCD I2C 20x4)
   DANIEL RODRIGUES DE SOUSA 19/04/2024 
   PROJETO: https://wokwi.com/projects/395613368896265217 */ 

#include <LiquidCrystal_I2C.h>  // Biblioteca para controle do LCD via I2C

// Define o número de colunas e linhas do LCD
#define COLUNAS 20
#define LINHAS  4

// Define o endereço do LCD, número de colunas e linhas
LiquidCrystal_I2C lcd(0x27, COLUNAS, LINHAS);  

void setup()
{
  // Inicializa o LCD
  lcd.init();
  // Liga a luz de fundo do LCD                      
  lcd.backlight();
}

void loop()
{
  // Posiciona o cursor na primeira coluna, primeira linha
  lcd.setCursor(0, 0);
  // Imprime a mensagem
  lcd.print("Hello, World!");
  delay(1000);  // Aguarda 1 segundo
  // Limpa o display para imprimir nova mensagem
  lcd.clear();
  // Posiciona o cursor na primeira coluna, segunda linha
  lcd.setCursor(0, 1);
  // Imprime a mensagem
  lcd.print("Hello, World!");
  delay(1000);  // Aguarda 1 segundo
  // Limpa o display
  lcd.clear(); 
}

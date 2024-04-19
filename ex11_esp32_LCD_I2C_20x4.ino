/* DÉCIMO PRIMEIRO PROGRAMA (ESP32 e LCD I2C 20x4)
   DANIEL RODRIGUES DE SOUSA 19/04/2024 */ 

#include <LiquidCrystal_I2C.h>

// define o número de colunas e linhas do LCD
#define COLUNAS 20
#define LINHAS  4

// define o endereço do LCD, número de colunas e linhas
LiquidCrystal_I2C lcd(0x27, COLUNAS, LINHAS);  

void setup(){
  // inicializa o LCD
  lcd.init();
  // liga a luz de fundo do LCD                      
  lcd.backlight();
}

void loop(){
  // posiciona o cursor na primeira coluna, primeira linha
  lcd.setCursor(0, 0);
  // imprime a mensagem
  lcd.print("Hello, World!");
  delay(1000);
  // limpa o display para imprimir nova mensagem
  lcd.clear();
  // posiciona o cursor na primeira coluna, segunda linha
  lcd.setCursor(0,1);
  // imprime a mensagem
  lcd.print("Hello, World!");
  delay(1000);
  // limpa o display
  lcd.clear(); 
}

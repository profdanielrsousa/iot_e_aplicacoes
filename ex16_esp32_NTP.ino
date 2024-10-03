/* DÉCIMO SEXTO PROGRAMA (ESP32 e NTP Client)
   DANIEL RODRIGUES DE SOUSA 28/04/2024
   PROJETO: https://wokwi.com/projects/396257110044148737 */

#include <NTPClient.h>  // inclui biblioteca para trabalhar com NTP (Network Time Protocol)
#include <WiFi.h>       // inclui biblioteca para conexão Wi-Fi
#include <WiFiUdp.h>    // inclui biblioteca para UDP sobre Wi-Fi
#include <LiquidCrystal_I2C.h> // inclui biblioteca para controle de LCD

// define o número de colunas e linhas do LCD
#define COLUNAS 20  // número de colunas no LCD
#define LINHAS 4    // número de linhas no LCD

// define o pino do LED (15)
#define LED 15

const char *ssid = "Wokwi-GUEST"; // nome da rede Wi-Fi
const char *password = "";        // senha da rede Wi-Fi vazia (não é necessário)

unsigned long int time_ms;  // variável para armazenar o tempo em milissegundos

bool flag_inicializacao = 0;// bandeira para inicialização do sistema

String atual, anterior = "";// strings para armazenar a hora atual e anterior

WiFiUDP ntpUDP; // objeto UDP para conexão com NTP
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -10800, 60000);  // cliente de tempo NTP

// define o endereço do LCD (0x27), número de colunas e linhas
LiquidCrystal_I2C lcd(0x27, COLUNAS, LINHAS);

void setup()
{
  pinMode(LED, OUTPUT); // configura pino do LED como saída

  Serial.begin(115200); // inicializa comunicação serial com taxa de 115.200 bps

  lcd.init();           // inicia o LCD
  lcd.backlight();      // liga a luz de fundo do LCD

  WiFi.begin(ssid, password); // conecta-se à rede Wi-Fi com nome e senha fornecidos

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);           // aguarda 0.5 segundos
    lcd.setCursor(0, 0);  // posiciona o cursor na primeira coluna, primeira linha do LCD
    if(flag_inicializacao)
    {
      lcd.print("Conectando..."); // impressão da mensagem "Conectando..."
    }
    else
    {
      lcd.print("             "); // limpa o LCD antes do início da conexão Wi-Fi
    }

    Serial.print(".");  // imprime um ponto para indicar a progresso da inicialização
    flag_inicializacao = !flag_inicializacao; // alterna a flag de inicialização
  }

  Serial.println("\nConectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); // impressão do endereço IP local

  lcd.clear(); // limpa o LCD antes da impressão da mensagem final
  lcd.setCursor(0, 0);
  lcd.print("Conectado!");  // impressão da mensagem "Conectado!"
  lcd.setCursor(0, 1);
  lcd.print("IP: ");
  lcd.print(WiFi.localIP());// impressão do endereço IP local

  timeClient.begin(); // inicia o cliente de tempo NTP
}

void loop()
{
  if(millis() - time_ms >= 1000) 
  {
    time_ms = millis();
    timeClient.update(); // atualiza a hora com base no servidor NTP
    atual = timeClient.getFormattedTime();// obtém a hora formatada do cliente de tempo NTP
    digitalWrite(LED, !digitalRead(LED)); // alterna o estado do LED (luz)
  }

  if(atual != anterior) 
  {
    anterior = atual;
    Serial.println(atual);  // impressão da hora atual no console serial
    lcd.setCursor(0, 3);
    lcd.print(atual);       // impressão da hora atual na tela LCD
  }
}

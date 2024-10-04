/* DÉCIMO SÉTIMO PROGRAMA (ESP32 e ping)
   DANIEL RODRIGUES DE SOUSA 03/10/2024
   PROJETO: https://wokwi.com/projects/410768457765627905 */

#include <WiFi.h>       // inclui biblioteca para conexão Wi-Fi
#include <ESPping.h>    // inclui biblioteca para ping
#include <LiquidCrystal_I2C.h> // inclui biblioteca para controle de LCD

// define o número de colunas e linhas do LCD
#define COLUNAS 20  // número de colunas no LCD
#define LINHAS 4    // número de linhas no LCD

// define o pino do LED (15)
#define LED 15

const char *ssid = "Wokwi-GUEST"; // nome da rede Wi-Fi
const char *password = "";        // senha da rede Wi-Fi vazia (não é necessário)

bool flag_inicializacao = 0; // bandeira para inicialização do sistema

// define o endereço do LCD (0x27), número de colunas e linhas
LiquidCrystal_I2C lcd(0x27, COLUNAS, LINHAS);

const char *host = "www.google.com"; // nome do host a ser resolvido
IPAddress ip; // variável para armazenar o endereço IP

void setup()
{
  pinMode(LED, OUTPUT); // configura pino do LED como saída

  Serial.begin(115200); // inicializa comunicação serial com taxa de 115.200 bps

  lcd.init();           // inicia o LCD
  lcd.backlight();      // liga a luz de fundo do LCD

  WiFi.begin(ssid, password); // conecta-se à rede Wi-Fi com nome e senha fornecidos

  while(WiFi.status() != WL_CONNECTED) 
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

    Serial.print(".");  // imprime um ponto para indicar o progresso da inicialização
    flag_inicializacao = !flag_inicializacao; // alterna a flag de inicialização
  }

  Serial.println("\nConectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); // impressão do endereço IP local

  lcd.clear(); // limpa o LCD antes da impressão da mensagem final
  lcd.setCursor(0, 0);
  lcd.print("Conectado!");  // impressão da mensagem "Conectado!"
  lcd.setCursor(0, 1);
  lcd.print("Loc.:");
  lcd.print(WiFi.localIP()); // impressão do endereço IP local

  if(WiFi.hostByName(host, ip))
  {
    Serial.print("IP do site ");
    Serial.print(host);
    Serial.print(" eh: ");
    Serial.println(ip);

    lcd.setCursor(0, 2);
    lcd.print("Host:");
    lcd.print(ip); // impressão do endereço IP do host
  }
  else
  {
    Serial.println("Falha ao resolver o nome do domínio");
    while(1); // loop infinito em caso de falha na resolução do domínio
  }     
}

void loop()
{
  if(Ping.ping(host))
  {
    lcd.setCursor(0, 3);
    lcd.print("Ping: ");
    lcd.print(Ping.averageTime());
    lcd.print(" ms"); // impressão do tempo médio de ping
    Serial.print(Ping.averageTime()); // impressão do tempo médio de ping na serial
    Serial.println(" ms");
  }
  else
  {
    Serial.println("Sem resposta do host."); // mensagem de erro se o host não responder ao ping
  }
}

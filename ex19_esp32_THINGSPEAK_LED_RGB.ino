/* DÉCIMO NONO PROGRAMA (IoT COM THINGSPEAK, ESP32 E LED RGB)
   DANIEL RODRIGUES DE SOUSA 03/05/2024 */ 

#include <WiFi.h>         // Biblioteca para comunicação Wi-Fi
#include <ThingSpeak.h>   // Biblioteca para envio de dados para o ThingSpeak

#define LED_RED   5       // Define a porta do pino do LED vermelho
#define LED_GREEN 17      // Define a porta do pino do LED verde
#define LED_BLUE  16      // Define a porta do pino do LED azul

#define LED_RED_FIELD   1 // Campo para o status do LED vermelho no ThingSpeak
#define LED_GREEN_FIELD 2 // Campo para o status do LED verde no ThingSpeak
#define LED_BLUE_FIELD  3 // Campo para o status do LED azul no ThingSpeak

#define ssid  "Wokwi-GUEST" // Dados da sua rede Wi-Fi (nome)
#define senha ""            // Senha da rede Wi-Fi (deixe em branco se não tiver)

                                      // OBS: Altere de acordo com os dados da conta do ThingSpeak
#define myChannelNumber 1234567       // Número do canal no ThingSpeak onde você deseja enviar os dados
#define myApiKey  "ABCDEFGHIJKLMNOP"  // Chave de API para o seu canal no ThingSpeak

#define server "api.thingspeak.com"   // Endereço da API do ThingSpeak

WiFiClient client;

int led_red_status = 0;   // Variável para armazenar o status do LED vermelho
int led_green_status = 0; // Variável para armazenar o status do LED verde
int led_blue_status = 0;  // Variável para armazenar o status do LED azul

int status;

void setup()
{
   pinMode(LED_RED, OUTPUT);   // Configuração da direção dos pinos do LED RGB
   pinMode(LED_GREEN, OUTPUT);
   pinMode(LED_BLUE, OUTPUT);
   
  Serial.begin(115200); // Define a taxa de transferência serial (115,2 kbps)

  delay(100);

  Serial.print("Se conectando a: ");
  Serial.println(ssid); // Imprime o nome da rede Wi-Fi

  WiFi.begin(ssid, senha);  // Se conecta ao Wi-Fi com as credenciais definidas

  while (WiFi.status() != WL_CONNECTED) // Verifica se a conexão foi bem-sucedida
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); // Imprime o endereço de IP do ESP32

  ThingSpeak.begin(client);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}

void loop()
{
    led_red_status = ThingSpeak.readLongField(myChannelNumber, LED_RED_FIELD,  myApiKey);     // Lê o status do LED vermelho no ThingSpeak
    led_green_status = ThingSpeak.readLongField(myChannelNumber, LED_GREEN_FIELD,  myApiKey); // Lê o status do LED verde no ThingSpeak
    led_blue_status = ThingSpeak.readLongField(myChannelNumber, LED_BLUE_FIELD,  myApiKey);   // Lê o status do LED azul no ThingSpeak

    if(led_red_status == 1)
    {
        digitalWrite(LED_RED, HIGH);
        Serial.println("LED_RED ligado!");    // Imprime "LED vermelho ligado!"
    }
    else if(led_red_status == 0)
    {
        digitalWrite(LED_RED, LOW);
        Serial.println("LED_RED desligado!"); // Imprime "LED vermelho desligado!"
    }

    if(led_green_status == 1)
    {
        digitalWrite(LED_GREEN, HIGH);
        Serial.println("LED_GREEN ligado!");    // Imprime "LED verde ligado!"
    }
    else if(led_green_status == 0)
    {
        digitalWrite(LED_GREEN, LOW);
        Serial.println("LED_GREEN desligado!"); // Imprime "LED verde desligado!"
    }

    if(led_blue_status == 1)
    {
        digitalWrite(LED_BLUE, HIGH);
        Serial.println("LED_BLUE ligado!");     // Imprime "LED azul ligado!"
    }
    else if(led_blue_status == 0)
    {
        digitalWrite(LED_BLUE, LOW);
        Serial.println("LED_BLUE desligado!");  // Imprime "LED azul desligado!"
    }

    status = ThingSpeak.getLastReadStatus();    // Lê o status da última leitura no ThingSpeak

    if(status == 200)
    {
        Serial.println("Dados recebidos com sucesso");    // Imprime "Dados recebidos com sucesso"
    }
    else
    {
        Serial.println("Erro de envio " + String(status));// Imprime o erro de envio
    }

    Serial.println("---");

    delay(1000);  // Aguarda por 1 segundo antes de enviar os dados novamente
}

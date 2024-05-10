/* DÉCIMO SEXTO PROGRAMA (IoT COM THINGSPEAK, ESP32 E BOTÃO)
   DANIEL RODRIGUES DE SOUSA 10/05/2024 */ 

#include <WiFi.h>       // Biblioteca para comunicação Wi-Fi
#include <ThingSpeak.h> // Biblioteca para envio de dados para o ThingSpeak

#define BOTAO_RED   5       // Define a porta do pino do LED vermelho
#define BOTAO_GREEN 17      // Define a porta do pino do LED verde
#define BOTAO_BLUE  16      // Define a porta do pino do LED azul

#define ssid  "Wokwi-GUEST" // Dados da sua rede Wi-Fi
#define senha ""            // Senha da rede Wi-Fi (deixe em branco se não tiver)

                                      // OBS: Altere de acordo com os dados da conta do Thinkspeak
#define myChannelNumber 1234567       // Número do canal no ThingSpeak onde você deseja enviar os dados
#define myApiKey  "XXXXXXXXXXXXXXXX"  // Chave de API para o seu canal no ThingSpeak


#define server    "api.thingspeak.com"// Endereço da API do ThingSpeak

WiFiClient client;

int status;

void setup()
{
  pinMode(BOTAO_RED, INPUT);   // Configuração da direção dos pinos do LED RGB
  pinMode(BOTAO_GREEN, INPUT);
  pinMode(BOTAO_BLUE, INPUT);

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

  WiFi.mode(WIFI_STA);            // Define a modalidade da conexão Wi-Fi (modo estação)

  ThingSpeak.begin(client);
}

void loop()
{


  ThingSpeak.setField(1, digitalRead(BOTAO_RED));   // Define o valor para a campo 1 no ThingSpeak
  ThingSpeak.setField(2, digitalRead(BOTAO_GREEN)); // Define o valor para a campo 2 no ThingSpeak
  ThingSpeak.setField(3, digitalRead(BOTAO_BLUE));  // Define o valor para a campo 2 no ThingSpeak
  
  status = ThingSpeak.writeFields(myChannelNumber, myApiKey); // Envio dos dados para o ThingSpeak

  Serial.println("Botao RED: " + String(digitalRead(BOTAO_RED)));     // Imprime a temperatura
  Serial.println("Botao GREEN: " + String(digitalRead(BOTAO_GREEN))); // Imprime a temperatura
  Serial.println("Botao BLUE: " + String(digitalRead(BOTAO_BLUE)));   // Imprime a temperatura
  
  if(status == 200)
  {
    Serial.println("Dados enviados com sucesso");
  }
  else
  {
    Serial.println("Erro de envio " + String(status));
  }
 
  Serial.println("---");

  delay(10000); // Aguarda por 10 segundos antes de enviar os dados novamente
}
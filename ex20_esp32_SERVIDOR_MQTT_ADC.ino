/* VIGÉSIMO PROGRAMA (IoT COM SERVIDOR MQTT, ESP32 E ADC)
   DANIEL RODRIGUES DE SOUSA 17/05/2024 
   PROJETO: https://wokwi.com/projects/397460194908298241 */   

#include <WiFi.h>         // Inclui a biblioteca WiFi para comunicação Wi-Fi
#include <PubSubClient.h> // Inclui a biblioteca PubSubClient para comunicação MQTT

#define SSID        "Wokwi-GUEST"       // Define o nome da rede Wi-Fi
#define PASS        ""                  // Define a senha da rede Wi-Fi (vazia)
#define MQTTSERVER  "test.mosquitto.org"// Define o servidor MQTT
#define PORT        1883                // Define a porta do servidor MQTT

// Lista de servidores MQTT gratuitos
/*
test.mosquitto.org
broker.hivemq.com
mqtt.eclipseprojects.io
broker.emqx.io
*/

char clientId[50];  // Variável para armazenar o ID do cliente MQTT
char ad_array[5];   // Variável para armazenar o valor do ADC

WiFiClient espClient;           // Cria um objeto WiFiClient para comunicação Wi-Fi
PubSubClient client(espClient); // Cria um objeto PubSubClient para comunicação MQTT

unsigned long time_ms; // Variável para armazenar o tempo em milissegundos
unsigned int valor_ad; // Variável para armazenar o valor lido do ADC

void setup()
{
  Serial.begin(115200);      // Inicializa a serial com uma taxa de baudios de 115200
  delay(10);                 // Atraso de 10 milissegundos

  Serial.print("Se conectando a: "); // Imprime o nome da rede Wi-Fi
  Serial.println(SSID);              // Imprime o nome da rede Wi-Fi

  WiFi.begin(SSID, PASS); // Se conecta ao Wi-Fi com as credenciais definidas
  
  while (WiFi.status() != WL_CONNECTED) // Verifica se a conexão foi bem-sucedida
  {
    delay(1000);       // Atraso de 1 segundo
    Serial.print("."); // Imprime um ponto para indicar o progresso da conexão
  }

  WiFi.mode(WIFI_STA); // Define a modalidade da conexão Wi-Fi (modo estação)

  Serial.println(""); // Pula uma linha
  Serial.println("Conexão Wi-Fi realizada");
  Serial.print("Endereço IP: ");  // Imprime o endereço IP do dispositivo
  Serial.println(WiFi.localIP()); // Imprime o endereço IP local

  client.setServer(MQTTSERVER, PORT); // Define o servidor MQTT e a porta
  client.setCallback(callback);       // Define uma função de callback para lidar com as mensagens recebidas

  randomSeed(micros()); // Semente aleatória para gerar números aleatórios
}

void mqttReconnect()
{
  while (!client.connected()) // Verifica se a conexão MQTT não está estabelecida
  {
    Serial.print("Tentando conexão MQTT... ");  // Imprime uma mensagem indicando que a conexão MQTT está sendo tentada
    
    long r = random(1000);    // Gera um número aleatório para usar como ID do cliente
    sprintf(clientId, "clientId-%ld", r);       // Formata o ID do cliente com o número aleatório

    if (client.connect(clientId))   // Tenta se conectar ao servidor MQTT com o ID do cliente
    {
      Serial.print(clientId);       // Imprime o ID do cliente conectado
      Serial.println(" conectado"); // Imprime uma mensagem indicando que a conexão foi estabelecida
    
      client.subscribe("topicName");// Se inscreve no tópico "topicName"
    }
    else
    {
      Serial.print("Falha, rc=");   // Imprime um erro de conexão MQTT
      Serial.print(client.state()); // Imprime o estado da conexão MQTT
      Serial.println(" tentando novamente em 5 segundos"); // Imprime uma mensagem indicando que a conexão será tentada novamente após 5 segundos
    
      delay(5000); // Atraso de 5 segundos antes de tentar se conectar novamente
    }
  }
}

void callback(char* topic, byte* message, unsigned int length)
{
  Serial.print("Mensagem recebida no tópico: "); // Imprime o nome do tópico que a mensagem foi enviada
  Serial.print(topic);           // Imprime o nome do tópico
  Serial.print(". Mensagem: ");  // Imprime uma mensagem indicando que uma mensagem foi recebida
  
  String stMessage; // Variável para armazenar a mensagem recebida como string

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]); // Imprime cada caractere da mensagem
    stMessage += (char)message[i];  // Adiciona cada caractere à variável de armazenamento
  }
}

void loop()
{
  if (!client.connected())  // Verifica se a conexão MQTT não está estabelecida
  {
    mqttReconnect();  // Tenta se conectar ao servidor MQTT novamente
  }

  client.loop();      // Mantém a conexão MQTT ativa

  if (millis() - time_ms >= 500) 
  {
    time_ms = millis(); 
    valor_ad = analogRead(39);            // Lê o valor do ADC
    sprintf(ad_array, "%04d", valor_ad);  // Formata o valor lido em uma string
    Serial.print("ADC: "); 
    Serial.println(ad_array); 
    client.publish("esp32/adc", ad_array);// Publica o valor lido no tópico "esp32/adc"
  }
}

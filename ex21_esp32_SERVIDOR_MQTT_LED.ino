/* VIGÉSIMO PRIMEIRO PROGRAMA (IoT COM SERVIDOR MQTT, ESP32 E LED)
   DANIEL RODRIGUES DE SOUSA 10/05/2024 
   PROJETO: https://wokwi.com/projects/397368477018263553 */   
  
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

#define LED   2   // Definição do pino do LED

char clientId[50]; // Variável para armazenar o ID do cliente MQTT

WiFiClient espClient;           // Criação de uma instância da classe WiFiClient para comunicação Wi-Fi
PubSubClient client(espClient); // Criação de uma instância da classe PubSubClient, que utiliza a instância WiFiClient como conexão

void setup()
{
  Serial.begin(115200); // Inicializa a serial com uma taxa de baudios de 115200
  
  delay(10);            // Atraso de 10 milissegundos

  Serial.print("Se conectando a: ");  // Imprime o nome da rede Wi-Fi
  Serial.println(SSID);               // Imprime o nome da rede Wi-Fi

  WiFi.begin(SSID, PASS);             // Conecta-se ao Wi-Fi com as credenciais definidas
  
  while(WiFi.status() != WL_CONNECTED) // Verifica se a conexão foi bem-sucedida
  {
    delay(1000);      // Atraso de 1 segundo
    Serial.print(".");// Imprime um ponto para indicar o progresso da conexão
  }

  WiFi.mode(WIFI_STA); // Define a modalidade da conexão Wi-Fi (modo estação)

  Serial.println(""); // Pula uma linha
  Serial.println("Conexão Wi-Fi realizada");
  Serial.print("Endereço IP: ");  // Imprime o endereço IP do dispositivo
  Serial.println(WiFi.localIP()); // Imprime o endereço IP local

  client.setServer(MQTTSERVER, PORT); // Define o servidor MQTT e a porta
  client.setCallback(callback);       // Define uma função de callback para lidar com as mensagens recebidas

  pinMode(LED, OUTPUT); // Configura o pino LED como saída

  randomSeed(micros()); // Inicializa a semente aleatória para gerar números aleatórios
}

void mqttReconnect()
{
  while(!client.connected()) // Verifica se a conexão MQTT não está estabelecida
  {
    Serial.print("Tentando conexão MQTT... "); // Imprime uma mensagem indicando que o ESP32 está tentando se conectar ao servidor MQTT
    long r = random(1000);                     // Gera um valor aleatório para ser usado como ID do cliente MQTT
    sprintf(clientId, "clientId-%ld", r);      // Converte o valor aleatório em string e armazena no ID do cliente MQTT

    if(client.connect(clientId)) // Tenta se conectar ao servidor MQTT com o ID do cliente gerado
    {
      Serial.print(clientId);
      Serial.println(" conectado");     // Imprime uma mensagem indicando que a conexão ao servidor MQTT foi bem-sucedida
      client.subscribe("topicName/led");// Inscreve o ESP32 para receber mensagens do tópico "topicName/led"
    }
    else
    {
      Serial.print("falhou, rc="); 
      Serial.print(client.state()); 
      Serial.println(" tentando novamente em 5 segundos"); // Imprime uma mensagem indicando que a conexão ao servidor MQTT falhou e o ESP32 está tentando se conectar novamente
      delay(5000); // Atraso de 5 segundos antes de tentar se conectar novamente
    }
  }
}

void callback(char* topic, byte* message, unsigned int length)
{
  Serial.print("Mensagem recebida no tópico: "); // Imprime o nome do tópico que a mensagem foi enviada
  Serial.print(topic);                           // Imprime o nome do tópico
  Serial.print(". Mensagem: ");                  // Imprime uma mensagem indicando que uma mensagem foi recebida
  
  String stMessage; // Variável para armazenar a mensagem recebida como string

  for(int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]); // Imprime cada caractere da mensagem
    stMessage += (char)message[i];  // Adiciona cada caractere à variável de armazenamento
  }

  Serial.println(""); 

  if(String(topic) == "topicName/led") // Verifica se o tópico é "topicName/led"
  {
    Serial.print("Alterando saída para ");
    if(stMessage == "on")     // Se a mensagem for "on", liga o LED
    {
      Serial.println("ligado");
      digitalWrite(LED, HIGH);// Liga o LED
    }
    else if(stMessage == "off") // Se a mensagem for "off", desliga o LED
    {
      Serial.println("desligado");
      digitalWrite(LED, LOW);   // Desliga o LED
    }
  }
}

void loop()
{
  if(!client.connected()) // Verifica se a conexão MQTT não está estabelecida
  {
    mqttReconnect();      // Tenta se conectar ao servidor MQTT novamente
  }

  client.loop();          // Mantém a conexão com o servidor MQTT ativa
}

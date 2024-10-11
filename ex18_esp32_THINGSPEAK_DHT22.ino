/* DÉCIMO OITAVO PROGRAMA (IoT COM THINGSPEAK, ESP32 E SENSOR DHT22)
   DANIEL RODRIGUES DE SOUSA 03/05/2024 
   PROJETO: https://wokwi.com/projects/396776488283018241 */
   
#include <DHT.h>        // Biblioteca do sensor DHT22 (para leitura de temperatura e umidade)
#include <WiFi.h>       // Biblioteca para comunicação Wi-Fi
#include <ThingSpeak.h> // Biblioteca para envio de dados para o ThingSpeak

#define DHT_PIN 13      // Define o pino para a conexão do sensor DHT22 (altere se necessário)

DHT dht(DHT_PIN, DHT22);// Cria um objeto para controlar o sensor DHT22

#define ssid  "Wokwi-GUEST" // Nome da rede Wi-Fi
#define senha ""            // Senha da rede Wi-Fi (deixe em branco se não tiver)

                                      // OBS: Altere de acordo com os dados da conta do ThingSpeak
#define myChannelNumber 1234567       // Número do canal no ThingSpeak onde você deseja enviar os dados
#define myApiKey  "ABCDEFGHIJKLMNOP"  // Chave de API para o seu canal no ThingSpeak (Write API Key)

#define server    "api.thingspeak.com"// Endereço da API do ThingSpeak

WiFiClient client;

int status;

void setup()
{
  dht.begin();          // Inicia a comunicação com o sensor DHT22
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

  ThingSpeak.begin(client);       // Inicia a comunicação com o ThingSpeak
}

void loop()
{
  dht.read(); // Lê as medições do sensor DHT22 (temperatura e umidade)
 
  ThingSpeak.setField(1, dht.readTemperature());  // Define o valor para o campo 1 no ThingSpeak
  ThingSpeak.setField(2, dht.readHumidity());     // Define o valor para o campo 2 no ThingSpeak
  
  status = ThingSpeak.writeFields(myChannelNumber, myApiKey); // Envia os dados para o ThingSpeak

  Serial.println("Temperatura: " + String(dht.readTemperature(), 2) + "°C");  // Imprime a temperatura
  Serial.println("Umidade relativa: " + String(dht.readHumidity(), 1) + "%"); // Imprime a umidade
  
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

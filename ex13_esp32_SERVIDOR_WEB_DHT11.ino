/* DÉCIMO TERCEIRO PROGRAMA (ESP32, SERVIDOR WEB E SENSOR DHT11)
   DANIEL RODRIGUES DE SOUSA 28/04/2024 */ 

#include <WiFi.h>       // Inclusão das bibliotecas para comunicação Wi-Fi e servidor web
#include <WebServer.h>  // Biblioteca do servidor web
#include <DHT.h>        // Biblioteca do sensor DHT11

#define DHT_PIN 27      // Define o pino para a conexão do sensor DHT11 (altere se necessário)
DHT dht(DHT_PIN, DHT11);// Cria um objeto para controlar o sensor DHT11. Caso use o DHT22, troque a constante DHT11 para DHT22

WebServer sv(80);       // Define o servidor web na porta 80 (padrão)

const char* ssid = "NOME_REDE";   // Dados da sua rede Wi-Fi
const char* senha = "SENHA";

void conectado(void)    // Função onde será executado o script HTML para mostrar as medições do sensor DHT11
{   
  dht.read();           // Lê as medições do sensor DHT11 (temperatura e umidade)
  // Envia ao servidor o script HTML com os parâmetros de pressão e temperatura
  sv.send(200, "text/html", html((float)dht.readTemperature(), (float)dht.readHumidity()));
}

void nao_encontrado(void) // Sub-rotina para caso seja retornado um erro (404)
{
  // Retorna a mensagem de erro em caso de um retorno 404   
  sv.send(404, "text/plain", "Não encontrado");
}

String html(float temperatura, float umidade) 
{
  String cd = "<!DOCTYPE html>\n";     // Variável que armazenará o script HTML

  cd += "<html lang=\"pt-br\">\n";
  cd += "<head>\n";
  cd += "<meta http-equiv=\"refresh\" content=\"5\">\n";
  cd += "<meta charset=\"utf-8\"/>\n";
  cd += "<title>ESP32 Pinos</title>\n";
  cd += "</head>\n";

  cd += "<body>\n";
  cd += "<img src=\"http://www.fatecitaquera.edu.br/images/bani2.png\">\n";   // Imagem de fundo
  cd += "<h1>ESP32 com DHT22</h1>\n";
  cd += "<p>Temperatura: ";   
  cd += (float)temperatura;
  cd += " °C</p>\n";
  cd += "<p>Umidade: ";
  cd += (float)umidade;
  cd += " %</p>\n";  
  cd += "</body>\n";  
  cd += "</html>\n";

  return cd;   // Retorna o script HTML
} 

void setup() 
{
  dht.begin();          // Inicia a comunicação com o sensor DHT11

  Serial.begin(115200); // Inicia o monitor serial (velocidade de 115.200 bps)

  delay(100);

  Serial.print("Se conectando a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);   // Se conecta ao Wi-Fi com as credenciais definidas

  while (WiFi.status() != WL_CONNECTED) // Verifica se a conexão foi bem-sucedida
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());   // Imprime o endereço de IP do ESP32

  sv.on("/", conectado);            // Define a rota "/" para executar a função "conectado"
  sv.onNotFound(nao_encontrado);    // Define a sub-rotina para caso seja retornado um erro (404)
  sv.begin();                       // Inicia o servidor web
  Serial.println("Servidor Online");
}

void loop() 
{
  sv.handleClient();  // Trata as solicitações do cliente e executa as funções definidas
}
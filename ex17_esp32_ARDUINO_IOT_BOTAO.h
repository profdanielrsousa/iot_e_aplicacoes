// Código gerado pela plataforma do Arduino IoT, NÃO EDITE.

#include <ArduinoIoTCloud.h>            // Biblioteca para comunicação com a nuvem do Arduino IoT
#include <Arduino_ConnectionHandler.h>  // Biblioteca para conexão Wi-Fi

const char DEVICE_LOGIN_NAME[]  = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"; // Nome de login do dispositivo na nuvem do Arduino IoT


// Define o nome da rede Wi-Fi (SSID) e senha
const char SSID[] =  "Wokwi-GUEST";                     // Nome da rede Wi-Fi (name)
const char PASS[] =  "";                                // Senha da rede Wi-Fi (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "XXXXXXXXXXXXXXXXXXXXXXXXX"; // Chave secreta do dispositivo para comunicação com a nuvem do Arduino IoT


bool botao1;  // Variável que armazena o estado do botão 1
bool botao2;  // Variável que armazena o estado do botão 2
bool botao3;  // Variável que armazena o estado do botão 3

void initProperties() { // Função que inicializa as propriedades do dispositivo na nuvem do Arduino IoT 
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME); // Define o nome de login do dispositivo na nuvem
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);// Define a chave secreta do dispositivo para comunicação com a nuvem
  
  // Adiciona as propriedades dos botões à nuvem do Arduino IoT
  ArduinoCloud.addProperty(botao1, READ, 1 * SECONDS, NULL); // Botão 1: leitura e atualização a cada 1 segundo
  ArduinoCloud.addProperty(botao2, READ, 1 * SECONDS, NULL); // Botão 2: leitura e atualização a cada 1 segundo
  ArduinoCloud.addProperty(botao3, READ, 1 * SECONDS, NULL); // Botão 3: leitura e atualização a cada 1 segundo
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS); // Define a conexão Wi-Fi preferida para o dispositivo

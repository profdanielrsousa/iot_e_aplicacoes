// Código gerado pela plataforma do Arduino IoT, NÃO EDITE.

#include <ArduinoIoTCloud.h>            // Biblioteca para comunicação com a nuvem do Arduino IoT
#include <Arduino_ConnectionHandler.h>  // Biblioteca para conexão Wi-Fi

const char DEVICE_LOGIN_NAME[]  = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"; // Nome de login do dispositivo na nuvem do Arduino IoT


// Define o nome da rede Wi-Fi (SSID) e senha
const char SSID[] =  "Wokwi-GUEST";                     // Nome da rede Wi-Fi (name)
const char PASS[] =  "";                                // Senha da rede Wi-Fi (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "XXXXXXXXXXXXXXXXXXXXXXXXX"; // Chave secreta do dispositivo para comunicação com a nuvem do Arduino IoT

void onLedBlueChange(); // Função chamada quando o valor de LedBlue for alterado na nuvem do Arduino IoT
void onLedGreenChange();// Função chamada quando o valor de LedGreen for alterado na nuvem do Arduino IoT
void onLedRedChange();  // Função chamada quando o valor de LedRed for alterado na nuvem do Arduino IoT

bool led_blue;  // Variável para armazenar o estado de LedBlue (true/false)
bool led_green; // Variável para armazenar o estado de LedGreen (true/false)
bool led_red;   // Variável para armazenar o estado de LedRed (true/false)

void initProperties() { // Função que inicializa as propriedades do dispositivo na nuvem do Arduino IoT
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME); // Define o nome do dispositivo na nuvem do Arduino IoT
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);// Define a chave secreta do dispositivo para comunicação com a nuvem do Arduino IoT
  ArduinoCloud.addProperty(led_blue, READWRITE, 1 * SECONDS, onLedBlueChange);  // Adiciona propriedade de leitura e escritura para LedBlue
  ArduinoCloud.addProperty(led_green, READWRITE, 1 * SECONDS, onLedGreenChange);// Adiciona propriedade de leitura e escritura para LedGreen
  ArduinoCloud.addProperty(led_red, READWRITE, 1 * SECONDS, onLedRedChange);    // Adiciona propriedade de leitura e escritura para LedRed

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS); // Define a conexão Wi-Fi preferida para o dispositivo

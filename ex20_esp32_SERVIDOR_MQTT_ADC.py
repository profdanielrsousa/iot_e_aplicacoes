# VIGÉSIMO PROGRAMA (IoT COM SERVIDOR MQTT, ESP32 E ADC)
# DANIEL RODRIGUES DE SOUSA 17/05/2024 
# PROJETO: https://wokwi.com/projects/397460194908298241 */
   
import time
import random
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import paho.mqtt.client as mqtt

# Usa a hora do sistema como seed para a geração de números aleatórios
random.seed(time.time())

# Gera um número aleatório entre 1000 e 10000
numero_aleatorio = random.randint(1000, 10000)

# Configurações do broker MQTT
broker = "test.mosquitto.org"
port = 1883
topic = "esp32/adc"
client_id = 'clientId-' + str(numero_aleatorio)

# Lista para armazenar os valores recebidos
dataList = []

# Função chamada quando uma nova mensagem é recebida
def on_message(client, userdata, message):
    try:
        # Converte a mensagem recebida para float e adiciona à lista
        adc_value = float(message.payload.decode('ascii'))
        dataList.append(adc_value)
    except:
        pass

# Configura o cliente MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1, client_id)
client.on_message = on_message

# Conecta ao broker MQTT
client.connect(broker, port, 60)

# Inscreve-se no tópico para receber mensagens
client.subscribe(topic)

# Inicia um loop em segundo plano para processar as mensagens recebidas
client.loop_start()

# Função para animar o gráfico
def animate(i, dataList):
    dataList = dataList[-50:]  # Mantém o tamanho da lista fixo
    ax.clear()                 # Limpa o último quadro de dados
    ax.plot(dataList)          # Plota o novo quadro de dados
    ax.set_ylim([0, 4200])     # Define o limite do eixo Y do gráfico
    ax.set_title("Dados do ESP32 ADC")  # Define o título da figura
    ax.set_ylabel("Valor ADC")          # Define o título do eixo Y

# Cria a figura para o gráfico
fig = plt.figure()
ax = fig.add_subplot(111)

# Animação do Matplotlib que cuida do gráfico em tempo real
ani = animation.FuncAnimation(fig, animate, fargs=(dataList,), interval=100)

plt.show()  # Mantém o gráfico do Matplotlib persistente na tela até ser fechado

# Quando o gráfico é fechado, para o loop do cliente MQTT e desconecta
client.loop_stop()
client.disconnect()

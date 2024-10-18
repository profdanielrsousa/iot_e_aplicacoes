#  VIGÉSIMO PRIMEIRO PROGRAMA (IoT COM SERVIDOR MQTT, ESP32 E LED)
#  DANIEL RODRIGUES DE SOUSA 10/05/2024 
#  PROJETO: https://wokwi.com/projects/397368477018263553 */  

import time
import random
import paho.mqtt.client as mqtt
from tkinter import Tk, Button

# Usa a hora do sistema como seed para a geração de números aleatórios
random.seed(time.time())

# Gera um número aleatório entre 1000 e 10000
numero_aleatorio = random.randint(1000, 10000)

# Configurações do cliente MQTT
broker = 'test.mosquitto.org'
port = 1883
topic = 'topicName/led'
client_id = 'clientId-' + str(numero_aleatorio)

# Definindo o tamanho dos botões
button_size = {'width': 10, 'height': 3}

# Função para enviar mensagem MQTT
def send_message(mensagem):
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1, client_id)
    client.connect(broker, port)
    client.publish(topic, mensagem)
    client.disconnect()

# Função chamada quando o botão Liga é pressionado
def liga():
    send_message('on')

# Função chamada quando o botão Desliga é pressionado
def desliga():
    send_message('off')

# Criando a janela principal
root = Tk()
root.title("Controle MQTT")

# Criando e posicionando os botões
Button(root, text="Liga", command=liga, width=button_size['width'], height=button_size['height']).pack(side='left')
Button(root, text="Desliga", command=desliga, width=button_size['width'], height=button_size['height']).pack(side='right')

# Iniciando o loop da interface gráfica
root.mainloop()

# DÉCIMO NONO PROGRAMA (IoT COM THINGSPEAK, ESP32 E LED RGB)
# DANIEL RODRIGUES DE SOUSA 17/10/2024
# PROJETO: https://wokwi.com/projects/396871558499573761

import time
import random
import requests
from tkinter import Tk, Button, Frame

# Configurações do ThingSpeak
channel_id = 'SEU_CHANNEL_ID'       # Substitua pelo seu channel ID
write_api_key = 'SEU_WRITE_API_KEY' # Substitua pelo seu Write API Key

# Definindo o tamanho dos botões
button_size = {'width': 20, 'height': 3}

# URL para fazer a requisição de dados ao ThingSpeak
url = f'https://api.thingspeak.com/update?api_key={write_api_key}'

# Função para enviar mensagem para ThingSpeak
def send_message(field, mensagem):
    try:
        # Envia uma requisição GET para ThingSpeak com os parâmetros adequados
        response = requests.get(url, params={'field' + str(field): mensagem})
        # Verifica se a requisição foi bem-sucedida
        if response.status_code == 200:
            print(f"Mensagem '{mensagem}' enviada com sucesso para o Field {field}.")
        else:
            print(f"Falha ao enviar mensagem '{mensagem}' para o Field {field}. Código de status: {response.status_code}")
    except requests.RequestException as e:
        # Trata exceções relacionadas à requisição HTTP
        print(f"Erro ao enviar mensagem: {e}")

# Função chamada quando o botão Liga é pressionado
def liga(field):
    send_message(field, '1')

# Função chamada quando o botão Desliga é pressionado
def desliga(field):
    send_message(field, '0')

# Criando a janela principal
root = Tk()
root.title("ThingSpeak (LED RGB)")

# Função para criar um conjunto de botões para um LED específico
def criar_botoes_led(cor, field):
    frame = Frame(root)
    frame.pack()
    Button(frame, text=f"Liga LED {cor}", command=lambda: liga(field), width=button_size['width'], height=button_size['height']).pack(side='left')
    Button(frame, text=f"Desliga LED {cor}", command=lambda: desliga(field), width=button_size['width'], height=button_size['height']).pack(side='right')

# Criando botões para os três LEDs (Vermelho, Verde e Azul)
criar_botoes_led("Vermelho", 1)
criar_botoes_led("Verde", 2)
criar_botoes_led("Azul", 3)

# Iniciando o loop da interface gráfica
root.mainloop()

# DÉCIMO OITAVO PROGRAMA (IoT COM THINGSPEAK, ESP32 E SENSOR DHT22)
# DANIEL RODRIGUES DE SOUSA 17/10/2024
# PROJETO: https://wokwi.com/projects/396776488283018241

import time
import random
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import requests

# Configurações do ThingSpeak
channel_id = 'SEU_CHANNEL_ID'       # Substitua pelo seu channel ID
read_api_key = 'SEU_READ_API_KEY'   # Substitua pelo seu Read API Key
field_number = 1    # O campo do canal de onde os dados serão lidos

# URL para fazer a requisição de dados ao ThingSpeak
url = f'https://api.thingspeak.com/channels/{channel_id}/fields/{field_number}.json?api_key={read_api_key}&results=10'

# Lista para armazenar os valores recebidos
dataList = []

# Função para buscar dados do ThingSpeak
def fetch_data():
    global dataList
    try:
        # Faz a requisição GET para obter os dados do ThingSpeak
        response = requests.get(url)
        response.raise_for_status() # Verifica se houve algum erro na requisição

        # Converte a resposta em JSON e extrai os dados do campo especificado
        data = response.json()
        dataList = [float(entry['field1']) for entry in data['feeds'] if entry['field1'] is not None]
    except requests.RequestException as e:
        # Trata exceções relacionadas à requisição HTTP
        print(f"Erro na requisição de dados: {e}")
        dataList = []   # Limpa a lista em caso de erro
    except ValueError as e:
        # Trata exceções relacionadas à conversão dos dados
        print(f"Erro ao processar os dados recebidos: {e}")
        dataList = []   # Limpa a lista em caso de erro

# Função para animar o gráfico
def animate(i):
    fetch_data()        # Atualiza os dados
    ax.clear()          # Limpa o último quadro de dados
    ax.plot(dataList)   # Plota o novo quadro de dados
    ax.set_ylim([0, 50])# Define o limite do eixo Y do gráfico
    ax.set_title("Dados do ThingSpeak (Temperatura)")   # Define o título da figura
    ax.set_ylabel("Temperatura (°C)")   # Define o título do eixo Y

# Cria a figura para o gráfico
fig = plt.figure()
ax = fig.add_subplot(111)

# Animação do Matplotlib que cuida do gráfico em tempo real
ani = animation.FuncAnimation(fig, animate, interval=15000) # Atualiza a cada 15 segundos

plt.show()  # Mantém o gráfico do Matplotlib persistente na tela até ser fechado

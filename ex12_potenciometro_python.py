#  DÉCIMO SEGUNDO PROGRAMA (ENVIO DE DADOS PARA O PYTHON VIA SERIAL)
#  REFERÊNCIA: https://github.com/WaveShapePlay/Arduino_RealTimePlot/tree/master
#  DANIEL RODRIGUES DE SOUSA 15/03/2024
   
import time
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def animate(i, dataList, ser):
    ser.write(b'g')                                     # Transmite o caractere 'g' para receber o ponto de dados do Arduino
    arduinoData_string = ser.readline().decode('ascii') # Decodifica os dados recebidos do Arduino como uma string formatada
    #print(i)                                           # 'i' é uma variável que incrementa com base nos frames = x argumento

    try:
        arduinoData_float = float(arduinoData_string)   # Converte para float
        dataList.append(arduinoData_float)              # Adiciona à lista que mantém o número fixo de pontos para animar

    except:                                             # Ignora se o ponto de dados for ruim                               
        pass

    dataList = dataList[-50:]                           # Fixa o tamanho da lista para que a janela de plotagem da animação seja de x pontos
    
    ax.clear()                                          # Limpa o último quadro de dados
    ax.plot(dataList)                                   # Plota o novo quadro de dados
    
    ax.set_ylim([0, 1200])                              # Define o limite do eixo Y do plot
    ax.set_title("Dados do Arduino")                    # Define o título da figura
    ax.set_ylabel("Valor")                              # Define o título do eixo Y 

dataList = []                                           # Cria uma lista vazia para uso posterior
                                                        
fig = plt.figure()                                      # Cria a figura dos plots do Matplotlib; fig é a janela de plotagem de 'nível superior'
ax = fig.add_subplot(111)                               # Adiciona um subplot à janela principal fig

ser = serial.Serial("COM3", 9600)                       # Estabelece um objeto Serial com a porta COM e a taxa BAUD para corresponder à Porta/taxa do Arduino
time.sleep(2)                                           # Atraso de tempo para a inicialização Serial do Arduino 

                                                        # Função de Animação do Matplotlib que cuida do plot em tempo real.
                                                        # Note que o parâmetro 'fargs' é onde passamos nossa dataList e objeto Serial. 
ani = animation.FuncAnimation(fig, animate, frames=100, fargs=(dataList, ser), interval=50) 

plt.show()                                              # Mantém o plot do Matplotlib persistente na tela até que seja fechado
ser.close()                                             # Fecha a conexão Serial quando o plot é fechado

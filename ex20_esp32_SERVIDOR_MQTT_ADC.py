# VIGÉSIMO PROGRAMA (IoT COM SERVIDOR MQTT, ESP32 E ADC)
# DANIEL RODRIGUES DE SOUSA 17/05/2024 
# PROJETO: https://wokwi.com/projects/397460194908298241

import time
import random
import logging
from collections import deque

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import paho.mqtt.client as mqtt

# ---------------------------------------------------------------------------
# Configuração de log (substitui prints soltos e bare except)
# ---------------------------------------------------------------------------
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
)
log = logging.getLogger(__name__)

# ---------------------------------------------------------------------------
# Configurações do broker MQTT
# ---------------------------------------------------------------------------
# Se broker.hivemq.com falhar (gaierror 11004), tente:
#   "test.mosquitto.org"  ou  "mqtt.eclipseprojects.io"
# O erro normalmente indica bloqueio de porta 1883 por firewall/antivírus,
# ou ausência de resolução DNS — verifique sua conexão e as regras de saída.
BROKER   = "test.mosquitto.org"
PORT     = 1883
TOPIC    = "esp32/adc"
KEEPALIVE = 60

random.seed(time.time())
CLIENT_ID = f"clientId-{random.randint(1000, 10000)}"

# ---------------------------------------------------------------------------
# Buffer circular: mantém automaticamente no máximo 50 amostras
# (evita o bug da lista que cresce sem limite e o rebind em animate())
# ---------------------------------------------------------------------------
MAX_SAMPLES = 50
data_buffer: deque[float] = deque(maxlen=MAX_SAMPLES)

# ---------------------------------------------------------------------------
# Callbacks MQTT — API v2 (sem DeprecationWarning)
# ---------------------------------------------------------------------------
def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        log.info("Conectado ao broker MQTT. Inscrevendo em '%s'…", TOPIC)
        client.subscribe(TOPIC)
    else:
        log.error("Falha na conexão — código: %s", reason_code)


def on_message(client, userdata, message):
    try:
        value = float(message.payload.decode("ascii"))
        data_buffer.append(value)
        log.debug("Valor recebido: %.2f", value)
    except ValueError as exc:
        log.warning("Payload inválido ignorado: %s (%s)", message.payload, exc)


def on_disconnect(client, userdata, flags, reason_code, properties):
    if reason_code != 0:
        log.warning("Desconexão inesperada — código: %s", reason_code)

# ---------------------------------------------------------------------------
# Configuração do cliente MQTT (API v2)
# ---------------------------------------------------------------------------
client = mqtt.Client(
    mqtt.CallbackAPIVersion.VERSION2,
    client_id=CLIENT_ID,
)
client.on_connect    = on_connect
client.on_message    = on_message
client.on_disconnect = on_disconnect

try:
    client.connect(BROKER, PORT, KEEPALIVE)
except OSError as exc:
    # gaierror é subclasse de OSError
    log.error(
        "Não foi possível conectar ao broker '%s:%s'.\n"
        "  → Verifique sua conexão, firewall e se a porta %s está liberada.\n"
        "  → Tente trocar BROKER por 'test.mosquitto.org'.\n"
        "  Erro original: %s",
        BROKER, PORT, PORT, exc,
    )
    raise SystemExit(1)

client.loop_start()

# ---------------------------------------------------------------------------
# Animação Matplotlib
# ---------------------------------------------------------------------------
fig, ax = plt.subplots()


def animate(_frame):
    """Atualiza o gráfico a cada intervalo."""
    ax.clear()
    ax.plot(list(data_buffer))        # deque → list para o Matplotlib
    ax.set_ylim(0, 4200)
    ax.set_xlim(0, MAX_SAMPLES)
    ax.set_title("Dados do ESP32 ADC")
    ax.set_xlabel("Amostras recentes")
    ax.set_ylabel("Valor ADC")
    ax.grid(True, linestyle="--", alpha=0.5)


ani = animation.FuncAnimation(fig, animate, interval=100, cache_frame_data=False)

log.info("Gráfico aberto. Feche a janela para encerrar.")
plt.show()  # bloqueia até a janela ser fechada

# ---------------------------------------------------------------------------
# Limpeza ao encerrar
# ---------------------------------------------------------------------------
client.loop_stop()
client.disconnect()
log.info("Cliente MQTT desconectado. Programa encerrado.")

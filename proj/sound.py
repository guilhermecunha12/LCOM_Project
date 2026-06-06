import time
import os
import sys
# Importa apenas a componente de som para que seja mais leve
from pygame import mixer

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SHARED_FILE = os.path.join(SCRIPT_DIR, "sound_trigger.txt")
SOUNDS_DIR = os.path.join(SCRIPT_DIR, "sounds")

# Inicializar o mixer de som na arranque do script
mixer.init()
mixer.set_num_channels(3)  # Configura para usar 2 canais de som

# Canal 0 para sons de fundo, canal 1 para efeitos sonoros
BG_CHANNEL = mixer.Channel(0)
FX_CHANNEL = mixer.Channel(1)
PHONE_CHANNEL = mixer.Channel(2)

BG_CHANNEL.set_volume(0.4)  # Ajusta o volume de fundo para ser mais baixo
PHONE_CHANNEL.set_volume(0.2)  # Ajusta o volume do telefone para ser mais baixo

# Sounds that loop as background ambience
BACKGROUND_SOUNDS = {"night_music", "lights_out"}


def stop():
    BG_CHANNEL.stop()
    FX_CHANNEL.stop()


def play(sound_file, sound_name):
    try:
        sound = mixer.Sound(sound_file)
        if sound_name in BACKGROUND_SOUNDS:
            BG_CHANNEL.play(sound, loops=-1)
        elif sound_name == "night_phone":
            PHONE_CHANNEL.play(sound, loops=-1)
        else:
            FX_CHANNEL.stop()
            FX_CHANNEL.play(sound)
    except Exception as e:
        print(f"[ERROR] Failed to play: {e}", file=sys.stderr)


while True:
    content = ""
    try:
        if os.path.exists(SHARED_FILE):
            with open(SHARED_FILE, "r+") as f:
                content = f.read().strip()
                if content:
                    f.seek(0)
                    f.truncate()
            if content == "stop":
                stop()
            elif content:
                sound_file = os.path.join(SOUNDS_DIR, content + ".wav")
                if os.path.exists(sound_file):
                    play(sound_file, content)
                else:
                    print(f"[ERROR] Sound not found: {sound_file}")
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
    time.sleep(0.1)

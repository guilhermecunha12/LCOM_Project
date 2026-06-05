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


def stop():
    # Pára instantaneamente todos os sons que estejam a tocar
    mixer.stop()


def play(sound_file):
    # Garante que um som que já esteja a tocar pare
    stop()
    # O Pygame pode carregar e iniciar sons sem bloquear o processo
    try:
        sound = mixer.Sound(sound_file)
        sound.play()
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
                    play(sound_file)
                else:
                    print(f"[ERROR] Sound not found: {sound_file}")
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
    time.sleep(0.1)

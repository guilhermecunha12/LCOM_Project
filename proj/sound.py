import time
import os
import sys
import subprocess

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SHARED_FILE = os.path.join(SCRIPT_DIR, "sound_trigger.txt")
SOUNDS_DIR = os.path.join(SCRIPT_DIR, "sounds")

def play(sound_file):
    // Play sound using platform-specific commands
    if sys.platform == "darwin":
        subprocess.Popen(["afplay", sound_file])
    elif sys.platform == "win32":
        import winsound
        winsound.PlaySound(sound_file, winsound.SND_FILENAME | winsound.SND_ASYNC)
    else:
        for player in ["aplay", "paplay", "ffplay"]:
            if subprocess.call(["which", player], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL) == 0:
                subprocess.Popen([player, sound_file])
                break

while True:
    try:
        if os.path.exists(SHARED_FILE):
            with open(SHARED_FILE, "r+") as f:
                content = f.read().strip()
                if content:
                    f.seek(0)
                    f.truncate()
            if content:
                sound_file = os.path.join(SOUNDS_DIR, content + ".wav")
                if os.path.exists(sound_file):
                    play(sound_file)
    except Exception as e:
        print(f"Error: {e}")
    time.sleep(0.1)

import time
import os
import sys
import subprocess

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SHARED_FILE = os.path.join(SCRIPT_DIR, "sound_trigger.txt")
SOUNDS_DIR = os.path.join(SCRIPT_DIR, "sounds")

current_process = None

def stop():
    global current_process
    if sys.platform == "win32":
        import winsound
        winsound.PlaySound(None, winsound.SND_PURGE)  # stops any winsound
    if current_process and current_process.poll() is None:
        current_process.kill()
        current_process.wait()
    current_process = None

def play(sound_file):
    global current_process
    stop()  # stop whatever is playing first
    if sys.platform == "darwin":
        current_process = subprocess.Popen(["afplay", sound_file])
    elif sys.platform == "win32":
        import winsound
        # SND_ASYNC alone is not stoppable, run afplay equivalent via Popen
        current_process = subprocess.Popen(
            ["powershell", "-c",
             f"(New-Object Media.SoundPlayer '{sound_file}').PlaySync()"]
        )
    else:
        for player in ["aplay", "paplay", "ffplay"]:
            if subprocess.call(["which", player],
                               stdout=subprocess.DEVNULL,
                               stderr=subprocess.DEVNULL) == 0:
                current_process = subprocess.Popen([player, sound_file])
                break

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
    except Exception as e:
        print(f"Error: {e}")
    time.sleep(0.1)
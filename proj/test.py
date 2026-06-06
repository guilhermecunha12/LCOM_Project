import time
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SHARED_FILE = os.path.join(SCRIPT_DIR, "sound_trigger.txt")
SOUNDS_DIR = os.path.join(SCRIPT_DIR, "sounds")

with open(SHARED_FILE, "w") as f:
    f.write("night_music")

time.sleep(4)

with open(SHARED_FILE, "w") as f:
    f.write("monitor")

with open(SHARED_FILE, "w") as f:
    f.write("blip")

time.sleep(4)

with open(SHARED_FILE, "w") as f:
    f.write("night_phone")

time.sleep(4)

with open(SHARED_FILE, "w") as f:
    f.write("monitor")
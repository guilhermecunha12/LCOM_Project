#include <stdio.h>

/**
 * @brief This module interacts with a python code that runs on the HOST machine to play sound effects. It does so by writing the name of the sound effect to a specific file, which the python code monitors for changes. When a new sound name is written, the python code plays the corresponding sound effect. This allows for a simple and effective way to trigger sound effects from the game without needing complex audio handling within the game itself.
 */
#define SOUND_TRIGGER_PATH "/home/lcom/labs/proj/sound_trigger.txt"

void play_sound(const char *sound_name) {
    FILE *f = fopen(SOUND_TRIGGER_PATH, "w");
    if (!f) return;
    fprintf(f, "%s\n", sound_name);
    fclose(f);
}

void stop_sound(void) {
    FILE *f = fopen(SOUND_TRIGGER_PATH, "w");
    if (!f) return;
    fprintf(f, "stop\n");
    fclose(f);
}

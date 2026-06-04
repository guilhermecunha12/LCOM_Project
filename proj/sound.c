#include <stdio.h>

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

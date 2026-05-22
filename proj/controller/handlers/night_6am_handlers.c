#include "processor.h"

void handle_night_6am_timer(GameState* state, const GameEvent* event) {
    state->data.night_6am.duration--;
    if (state->data.night_6am.duration <= 0) {
        state->global_data.current_night++;
        if (state->global_data.current_night == NUM_NIGHTS) {
            state->type = WIN;
            state->data.win = init_win_screen();
        }else {
            state->type = NIGHT_INTRO;
            state->data.night_intro = init_night_intro();
        }
    }
}

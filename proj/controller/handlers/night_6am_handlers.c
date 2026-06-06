#include "processor.h"
#include "../../sound.h"

void handle_night_6am_timer(GameState* state, const GameEvent* event) {

    state->data.night_6am.duration--;

    if (state->data.night_6am.duration <= 0) {
        state->global_data.current_night++;

        if (state->global_data.current_night == NUM_NIGHTS) {
            state->global_data.current_night = 0;

            stop_sound();
            init_win_screen(state);

        }else {

            stop_sound();
            init_night_intro(state);
        }
    }
}

#include "processor.h"

void handle_win_screen_timer(GameState* state, const GameEvent* event) {

    state->data.win.duration--;

    if (state->data.win.duration <= 0) {
        init_main_menu(state);
    }
}

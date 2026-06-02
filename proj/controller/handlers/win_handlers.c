#include "processor.h"

void handle_win_screen_timer(GameState* state, const GameEvent* event) {
    // Decrement the time left on the win screen
    state->data.win.duration--;

    if (state->data.win.duration <= 0) {
        state->type = MAIN_MENU; // Go back to main menu after win screen
    }
}

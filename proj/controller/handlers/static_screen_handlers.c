#include "processor.h"

void handle_static_screen_timer(GameState* state, const GameEvent* event) {
    // Decrement the time left on the static screen
    state->data.static_screen.duration--;

    if (state->data.static_screen.duration == 0) {
        state->type = GAME_OVER; // Go to game over screen after static screen
    }
}
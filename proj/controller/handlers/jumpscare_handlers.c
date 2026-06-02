#include "processor.h"

void handle_jumpscare_timer(GameState* state, const GameEvent* event) {
    state->data.jumpscare.duration--;

    if (state->data.jumpscare.duration <= 0) {
        // After the jumpscare duration, transition to the win screen
        state->type = STATIC_SCREEN;
        state->data.static_screen = init_static_screen();
    }
}

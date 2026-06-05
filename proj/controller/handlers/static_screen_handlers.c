#include "processor.h"

void handle_static_screen_timer(GameState* state, const GameEvent* event) {

    state->data.static_screen.duration--;
    animate_sprite(state->data.static_screen.static_sprite);

    if (state->data.static_screen.duration <= 0) {
        init_game_over(state);
    }
}

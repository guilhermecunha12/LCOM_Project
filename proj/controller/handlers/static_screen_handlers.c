#include "processor.h"

void handle_static_screen_timer(GameState* state, const GameEvent* event) {
    StaticScreenState* s = &state->data.static_screen;

    animate_sprite(s->static_sprite);
    s->duration--;

    if (s->duration <= 0) {
        init_game_over(state);
    }
}

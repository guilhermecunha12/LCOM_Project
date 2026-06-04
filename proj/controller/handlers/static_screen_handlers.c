#include "processor.h"

void handle_static_screen_timer(GameState* state, const GameEvent* event) {
    // Decrement the time left on the static screen
    // TODO: chamar o anim sprite
    animate_sprite_once(state->data.static_screen.static_sprite);

    if (state->data.static_screen.static_sprite->is_finished) {
        state->type = NIGHT_INTRO;
        init_night_intro(state);
    }
}

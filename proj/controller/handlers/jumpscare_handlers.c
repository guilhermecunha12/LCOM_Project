#include "processor.h"
#include "../../models/assets.h"

void handle_jumpscare_timer(GameState* state, const GameEvent* event) {
    state->data.jumpscare.duration--;

    state->data.jumpscare.tick_timer++;
    if (state->data.jumpscare.tick_timer >= TICKS_PER_JUMPSCARE_FRAME) {
        state->data.jumpscare.tick_timer = 0;
        int max_frames = get_jumpscare_frame_count(state->data.jumpscare.animatronic_name, state->data.jumpscare.is_freddy_lightout);
        if (state->data.jumpscare.frame_index < max_frames - 1) {
            state->data.jumpscare.frame_index++;
        }
    }

    if (state->data.jumpscare.duration <= 0) {
        state->type = STATIC_SCREEN;
        state->data.static_screen = init_static_screen();
    }
}

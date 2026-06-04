#include "processor.h"
#include "../../models/assets.h"
#include "../../models/sprite.h"
#include "../../sound.h"

void handle_jumpscare_timer(GameState* state, const GameEvent* event) {
    if (!state->data.jumpscare.jumpscare_sprite->cur_fig)
        play_sound("jumpscare");
    animate_sprite_once(state->data.jumpscare.jumpscare_sprite);

    if(state->data.jumpscare.jumpscare_sprite->is_finished) {
        stop_sound();
        init_static_screen(state);
    }
}

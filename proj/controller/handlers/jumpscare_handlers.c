#include "processor.h"
#include "../../models/assets.h"
#include "../../models/sprite.h"

void handle_jumpscare_timer(GameState* state, const GameEvent* event) {
    
    animate_sprite_once(state->data.jumpscare.jumpscare_sprite);
    if(state->data.jumpscare.jumpscare_sprite->is_finished) {
        init_static_screen(state);
    }
}

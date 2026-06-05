#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"

void render_jumpscare(const GameState *state) {
    if(state->type != JUMPSCARE) return;

    draw_sprite((Sprite *)state->data.jumpscare.jumpscare_sprite->sp);
}

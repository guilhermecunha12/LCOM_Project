#include <lcom/lcf.h>
#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"

void render_jumpscare(const GameState *state) {
    draw_sprite((Sprite *)state->data.jumpscare.jumpscare_sprite->sp);
}

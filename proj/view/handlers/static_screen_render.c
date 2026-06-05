#include <lcom/lcf.h>
#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"

void render_static_screen(const GameState* state) {
    if(state->type != STATIC_SCREEN) return;

    draw_sprite((Sprite *) state->data.static_screen.static_sprite->sp);
}

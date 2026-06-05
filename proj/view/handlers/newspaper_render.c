#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"

void render_newspaper(const GameState* state) {
    if (state->type != NEWSPAPER) return;
    
    draw_sprite(get_asset(NEWSPAPER_FEUP));
}

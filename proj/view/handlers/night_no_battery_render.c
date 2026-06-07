#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"


void render_night_no_battery(const GameState* state) {
    Sprite* office_sprite = get_asset(OFFICE_LIGHTS_OUT);
    office_sprite->x = state->global_data.background_offset_x;
    draw_sprite(office_sprite);
}

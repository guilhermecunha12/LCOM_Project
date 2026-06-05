#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"


void render_night_no_battery(const GameState* state) {
    draw_sprite(get_asset(OFFICE_LIGHTS_OUT));
}

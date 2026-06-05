#include "renderer.h"
#include "../../models/assets.h"

void render_waiting_for_data(const GameState* state) {
    draw_sprite(get_asset(WAITING_FOR_DATA_SCREEN));
}

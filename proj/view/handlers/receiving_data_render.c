#include "renderer.h"
#include "../../models/assets.h"

void render_receiving_data(const GameState* state) {
    draw_sprite(get_asset(RECEIVING_DATA_SCREEN));
}

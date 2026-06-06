#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"

void render_win_screen(const GameState* state) {
  if (state->type != WIN) return;

  draw_sprite(get_asset(WIN_SCREEN));
}

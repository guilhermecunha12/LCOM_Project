#include <lcom/lcf.h>
#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"

void render_night_6am(const GameState* state) {
  if (state->type != NIGHT_6AM) return;

  draw_sprite(get_asset(NIGHT_6AM_SCREEN));
}
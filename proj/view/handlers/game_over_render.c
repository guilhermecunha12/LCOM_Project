#include <lcom/lcf.h>
#include "../../models/sprite.h"

#include "../../models/assets.h"
#include "renderer.h"

void render_game_over(const GameState* state) {
  if (state->type != GAME_OVER) return;

  draw_sprite(get_asset(GAME_OVER_SCREEN));
}

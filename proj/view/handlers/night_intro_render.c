#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"

void render_night_intro(const GameState* state) {
  if (state != NIGHT_INTRO) return;

  draw_sprite(get_asset(MENU_NIGHT1));
}
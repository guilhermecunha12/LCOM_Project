#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"

void render_night_intro(const GameState* state) {
  if (state->type != NIGHT_INTRO) return;

  if (state->global_data.current_night == 1) {
    draw_sprite(get_asset(START_NIGHT1));
  } else if (state->global_data.current_night == 2) {
    draw_sprite(get_asset(START_NIGHT2));
  } else if (state->global_data.current_night == 3) {
    draw_sprite(get_asset(START_NIGHT3));
  } else if (state->global_data.current_night == 4) {
    draw_sprite(get_asset(START_NIGHT4));
  } else if (state->global_data.current_night == 5) {
    draw_sprite(get_asset(START_NIGHT5));
  }
}

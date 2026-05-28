#include "renderer.h"
#include "../../models/assets.h"
#include "../../models/sprite.h"
#include "../ui.h"

static RenderHandler rht[NUM_STATES] = {
    [MAIN_MENU] = render_main_menu,
    //[NIGHT_SURVIVAL] = render_night_survival,
    // Other states...
};

void render_main_menu(const GameState *state) {
  if (state == NULL)
    return;

  draw_sprite(get_asset(MENU_BG), 0, 0);
  draw_sprite(get_asset(GAME_TITLE), GAME_TITLE_X, GAME_TITLE_Y);

  if (state->data.main_menu.selected_option == 1)
    draw_sprite(get_asset(OPT_NEWGAME_SEL), NEW_GAME_SEL_X, NEW_GAME_SEL_Y);
  else
    draw_sprite(get_asset(OPT_NEWGAME), NEW_GAME_X, NEW_GAME_Y);

  if (state->global_data.current_night > 0) {
    if (state->data.main_menu.selected_option == 2) {
      draw_sprite(get_asset(OPT_CONTINUE_SEL), CONTINUE_SEL_X, CONTINUE_SEL_Y);
    } else {
      draw_sprite(get_asset(OPT_CONTINUE), CONTINUE_X, CONTINUE_Y);
    }

    switch (state->global_data.current_night) {
    case 1:
      draw_sprite(get_asset(MENU_NIGHT1), NIGHT_TEXT_X, NIGHT_TEXT_Y);
      break;
    case 2:
      draw_sprite(get_asset(MENU_NIGHT2), NIGHT_TEXT_X, NIGHT_TEXT_Y);
      break;
    case 3:
      draw_sprite(get_asset(MENU_NIGHT3), NIGHT_TEXT_X, NIGHT_TEXT_Y);
      break;
    case 4:
      draw_sprite(get_asset(MENU_NIGHT4), NIGHT_TEXT_X, NIGHT_TEXT_Y);
      break;
    case 5:
      draw_sprite(get_asset(MENU_NIGHT5), NIGHT_TEXT_X, NIGHT_TEXT_Y);
      break;
    default:
      break;
    }
  }
}

RenderHandler get_render_handler(StateType state) {
  if (state >= NUM_STATES) { // TODO: needed?
    return NULL;             // Invalid state
  }

  return rht[state];
}

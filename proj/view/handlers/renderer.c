#include "renderer.h"

/**
 * @brief Array of render handlers, indexed by StateType. Each entry corresponds to a specific game state and points to the appropriate rendering function for that state.
 */
static RenderHandler rht[NUM_STATES] = {
    [MAIN_MENU] = render_main_menu,
    [NEWSPAPER] = render_newspaper,
    [NIGHT_INTRO] = render_night_intro,
    [NIGHT_SURVIVAL] = render_night_survival,
    [JUMPSCARE] = render_jumpscare,
    [STATIC_SCREEN] = render_static_screen,
    [NIGHT_6AM] = render_night_6am,
    [GAME_OVER] = render_game_over,
    [NIGHT_NO_BATTERY] = render_night_no_battery
};

RenderHandler get_render_handler(const StateType state) {
  if (state >= NUM_STATES) {
    return NULL; // invalid state
  }

  return rht[state];
}

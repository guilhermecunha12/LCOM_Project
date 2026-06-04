#include "renderer.h"

static RenderHandler rht[NUM_STATES] = {
    [MAIN_MENU] = render_main_menu,
    [NEWSPAPER] = render_newspaper,
    [NIGHT_INTRO] = render_night_intro,
    [NIGHT_SURVIVAL] = render_night_survival,
    [JUMPSCARE] = render_jumpscare,
    [WAITING_FOR_DATA] = render_waiting_for_data,
    [RECEIVING_DATA] = render_receiving_data,
};

RenderHandler get_render_handler(const StateType state) {
  if (state >= NUM_STATES) {
    return NULL; // invalid state
  }

  return rht[state];
}

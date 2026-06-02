#include "renderer.h"

static RenderHandler rht[NUM_STATES] = {
    [MAIN_MENU] = render_main_menu,
    [NIGHT_INTRO] = render_night_intro,
    //[NIGHT_SURVIVAL] = render_night_survival,
    // Other states...
    [NIGHT_SURVIVAL] = render_night_survival,
};

RenderHandler get_render_handler(StateType state) {
  if (state >= NUM_STATES) { // TODO: needed?
    return NULL;             // Invalid state
  }

  return rht[state];
}

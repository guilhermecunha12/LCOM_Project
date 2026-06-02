#include "renderer.h"
#include "../../models/assets.h"
#include "../../models/sprite.h"
#include "../ui.h"

static RenderHandler rht[NUM_STATES] = {
    [MAIN_MENU] = render_main_menu,
    //[NIGHT_SURVIVAL] = render_night_survival,
    // Other states...
};

RenderHandler get_render_handler(StateType state) {
  if (state >= NUM_STATES) { // TODO: needed?
    return NULL;             // Invalid state
  }

  return rht[state];
}

#include "processor.h"
#include "../../view/ui.h"

void handle_night_intro_timer(GameState* state, const GameEvent* event) {

    state->data.night_intro.duration--;

    if (state->data.night_intro.duration <= 0) {
        state->type = NIGHT_SURVIVAL;
        state->data.night_survival = init_night_survival(state->global_data.current_night);
        state->global_data.background_offset_x = CENTER_BACKGROUND_OFFSET;
    }
}

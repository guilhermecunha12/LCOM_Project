#include "processor.h"
#include "../../view/ui.h"

void handle_night_intro_timer(GameState* state, const GameEvent* event) {

    state->data.night_intro.duration--;

    if (state->data.night_intro.duration <= 0) {
        init_night_survival(state);
    }
}

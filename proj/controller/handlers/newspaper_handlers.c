#include "processor.h"
#include "../../view/ui.h"

void handle_newspaper_timer(GameState* state, const GameEvent* event) {

    state->data.newspaper.duration--;

    if (state->data.newspaper.duration <= 0) {
        state->global_data.current_night = 1;
        init_night_intro(state);
    }
}

// TODO: REMOVE! ONLY FOR FASTER TESTING
void go_to_night_survive(GameState* state, const GameEvent* event) {
    state->global_data.current_night = 1;
    init_night_survival(state);
}

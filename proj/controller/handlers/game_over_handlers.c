#include "processor.h"
#include "../../models/assets.h"
#include "../../models/sprite.h"

void handle_game_over_timer(GameState* state, const GameEvent* event) {
    
    state->data.game_over.duration--;

    if (state->data.game_over.duration <= 0) {
        init_main_menu(state);
    }

}

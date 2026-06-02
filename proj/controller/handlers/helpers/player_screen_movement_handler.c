#include "player_screen_movement_handler.h"

void move_player_screen_left(GameState* state) {
    state->global_data.background_offset_x -= BACKGROUND_STEP_OFFSET;
    if (state->global_data.background_offset_x < -BACKGROUND_MAX_OFFSET) {
        state->global_data.background_offset_x = -BACKGROUND_MAX_OFFSET;
    }
}

void move_player_screen_right(GameState* state) {
    state->global_data.background_offset_x += BACKGROUND_STEP_OFFSET;
    if (state->global_data.background_offset_x > BACKGROUND_MAX_OFFSET) {
        state->global_data.background_offset_x = BACKGROUND_MAX_OFFSET;
    }
}

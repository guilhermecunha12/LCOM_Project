#include "player_screen_movement_handler.h"

void move_player_screen_left(GameState* state) {
    state->global_data.moving = LEFT;
}

void move_player_screen_right(GameState* state) {
    state->global_data.moving = RIGHT;
}

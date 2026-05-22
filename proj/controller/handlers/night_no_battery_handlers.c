#include "processor.h"

void handle_night_no_battery_timer(GameState* state, const GameEvent* event) {
    state->data.night_no_battery.time_left--;
    if (state->data.night_no_battery.time_left == 0) {
        state->type = NIGHT_6AM;
        state->data.night_6am = init_night_6am();
    }
}
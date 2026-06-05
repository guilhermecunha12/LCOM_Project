#include "processor.h"
#include "../handlers/helpers/player_screen_movement_handler.h"

void handle_night_no_battery_timer(GameState* state, const GameEvent* event) {
    
    NightNoBatteryState* blackout = &state->data.night_no_battery;

    blackout->time_left--;
    if (blackout->phase1_duration > 0) {
        blackout->phase1_duration--;
    } else {
        blackout->phase2_duration--;
    }
    
    // If both phases are over and the player is still alive, Freddy attacks for sure
    if (blackout->phase1_duration <= 0 && blackout->phase2_duration <= 0) {
        init_jumpscare(state, FREDDY);
        return;
    }

    if (blackout->time_left <= 0) {
        init_night_6am(state);
        return;
    }

    bool attacked = update_freddy_no_battery(
        &blackout->freddy,
        blackout->phase1_duration,
        blackout->phase2_duration
    );

    if (attacked) {
        init_jumpscare(state, FREDDY);
    }
}

void handle_night_no_battery_keyboard(GameState* state, const GameEvent* event) {
    if(event->data.key == KEY_LEFT) {
        move_player_screen_left(state);
    }
    else if(event->data.key == KEY_RIGHT) {
        move_player_screen_right(state);
    }
}

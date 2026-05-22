#include "processor.h"

void handle_night_intro_timer(GameState* state, const GameEvent* event) {
    // Setup animatronics for the night based on the current night number
    NightSurvivalState* night_state = &state->data.night;
    PersistentData* global_data = &state->global_data;

    // Restart the night if player losses

    if(global_data->last_night_result == NIGHT_WIN) {
        // The player passed the previous night, so we increase the difficulty by increasing the AI level of the animatronics and maybe changing their paths
        global_data->current_night++;
    }

    // Initialize night state based on the current night number

    night_state->time_left = 31800; // 8m 55s in ticks

    night_state->power_level = 100;

    night_state->power_drain_rate = DRAIN_RATE_PER_NIGHT[global_data->current_night - 1];

    night_state->left_door_closed = false;
    night_state->right_door_closed = false;
    night_state->camera_monitor_up = false;

    for(int i = 0; i < 4; i++) {
        initialize_animatronic(&night_state->animatronics[i], global_data->current_night);
    }

    // Transition to night survival after the intro animation is done
    state->type = NIGHT_SURVIVAL;
    global_data->last_night_result = NIGHT_UNKOWN; // reset last night result for the new night
}

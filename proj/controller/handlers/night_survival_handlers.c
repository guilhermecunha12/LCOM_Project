#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"
#include "../handlers/helpers/player_screen_movement_handler.h"

void handle_night_survival_mouse_click(GameState* state, const GameEvent* event) {
    int mouse_x = state->global_data.mouse_x;
    int mouse_y = state->global_data.mouse_y;

    if (state->data.night_survival.camera_monitor_up) {
        // If the camera monitor is up, check if the click was on a camera feed to switch to it
        if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1A_X,
            NIGHT_CAMERA_1A_Y,
            NIGHT_CAMERA_1A_W,
            NIGHT_CAMERA_1A_H)) {

            state->data.night_survival.viewing_camera = CAM_1A;
            }
        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1B_X,
            NIGHT_CAMERA_1B_Y,
            NIGHT_CAMERA_1B_W,
            NIGHT_CAMERA_1B_H)) {

            state->data.night_survival.viewing_camera = CAM_1B;
            }
        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_2A_X,
            NIGHT_CAMERA_2A_Y,
            NIGHT_CAMERA_2A_W,
            NIGHT_CAMERA_2A_H)) {

            state->data.night_survival.viewing_camera = CAM_2A;
            }
        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_2B_X,
            NIGHT_CAMERA_2B_Y,
            NIGHT_CAMERA_2B_W,
            NIGHT_CAMERA_2B_H)) {

            state->data.night_survival.viewing_camera = CAM_2B;
            }

    } else { // not checking the cameras

        // Clicked to close left door
        if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_LEFT_DOOR_BUTTON_X,
            NIGHT_LEFT_DOOR_BUTTON_Y,
            NIGHT_LEFT_DOOR_BUTTON_W,
            NIGHT_LEFT_DOOR_BUTTON_H)) {

            state->data.night_survival.left_door_closed = !state->data.night_survival.left_door_closed; // switch
            }

        // Clicked to close right door
        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_RIGHT_DOOR_BUTTON_X,
            NIGHT_RIGHT_DOOR_BUTTON_Y,
            NIGHT_RIGHT_DOOR_BUTTON_W,
            NIGHT_RIGHT_DOOR_BUTTON_H)) {

            state->data.night_survival.right_door_closed = !state->data.night_survival.right_door_closed; // switch
            }

        // Clicked to turn on/off left light
        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_LEFT_LIGHT_BUTTON_X,
            NIGHT_LEFT_LIGHT_BUTTON_Y,
            NIGHT_LEFT_LIGHT_BUTTON_W,
            NIGHT_LEFT_LIGHT_BUTTON_H)) {

            state->data.night_survival.left_light_on = !state->data.night_survival.left_light_on; // switch
            }

        // Clicked to turn on/off right light
        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_RIGHT_LIGHT_BUTTON_X,
            NIGHT_RIGHT_LIGHT_BUTTON_Y,
            NIGHT_RIGHT_LIGHT_BUTTON_W,
            NIGHT_RIGHT_LIGHT_BUTTON_H)) {

            state->data.night_survival.right_light_on = !state->data.night_survival.right_light_on; // switch
        }
    }
}

void handle_night_survival_timer(GameState* state, const GameEvent* event) {

    // DECREASE TIME LEFT

    // Decrease time left
    NightSurvivalState* night_state = &state->data.night_survival;
    night_state->time_left--; // This is in ticks

    // Check if the player has survived the night
    if(night_state->time_left <= 0) {
        // Player survived the night
        state->type = NIGHT_6AM;
        state->data.night_6am = init_night_6am();
        return;
    }

    // BATERRY DRAIN
    
    // Base: accumulate 1 per tick
    int drain_rate = 1;
    
    // Increase the drain rate based on the what the player is using
    if (night_state->left_door_closed) drain_rate += BATTERY_DRAIN_RATE_DOOR;
    if (night_state->right_door_closed) drain_rate += BATTERY_DRAIN_RATE_DOOR;
    if (night_state->left_light_on) drain_rate += BATTERY_DRAIN_RATE_LIGHT;
    if (night_state->right_light_on) drain_rate += BATTERY_DRAIN_RATE_LIGHT;
    if (night_state->camera_monitor_up) drain_rate += BATTERY_DRAIN_RATE_CAMERA;
    
    night_state->power_drain_accumulator += drain_rate;
    
    // Every 588 ticks (default), drain 1%
    if (night_state->power_drain_accumulator >= night_state->power_drain_rate) {
        night_state->power_level--;
        night_state->power_drain_accumulator -= night_state->power_drain_rate;
    }

    if (night_state->power_level == 0) {
        int remaining_time = state->data.night_survival.time_left;
        state->type = NIGHT_NO_BATTERY;
        state->data.night_no_battery = init_night_no_battery(remaining_time);
        return;
    }
    
    // ANIMATRONICS MOVEMENT

    for(AnimatronicName name = 0; name < NUM_ANIMATRONICS; name++) {
        
        bool attacked = update_animatronic(
            &night_state->animatronics[name], 
            night_state->time_left, 
            night_state->left_door_closed, 
            night_state->right_door_closed
        );

        if (attacked) { // jumpscare
            state->type = JUMPSCARE;
            state->data.jumpscare = init_jumpscare(night_state->animatronics[name].name);
            return;
        }
    }
}

void handle_night_survival_keyboard(GameState* state, const GameEvent* event) {
    if(event->data.key == KEY_SPACE) {
        state->data.night_survival.camera_monitor_up = !state->data.night_survival.camera_monitor_up; // switch    
    }
    // Add remaining functionality
    else if(event->data.key == KEY_LEFT) {
        move_player_screen_left(state);
    }
    else if(event->data.key == KEY_RIGHT) {
        move_player_screen_right(state);
    }
}

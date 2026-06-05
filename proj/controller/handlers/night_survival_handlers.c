#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"
#include "../handlers/helpers/player_screen_movement_handler.h"
#include "../../models/sprite.h"

#define NIGHT_LEFT_DOOR_BUTTON_W 50
#define NIGHT_LEFT_DOOR_BUTTON_H 50
#define NIGHT_LEFT_DOOR_BUTTON_X 50
#define NIGHT_LEFT_DOOR_BUTTON_Y 400
#define NIGHT_RIGHT_DOOR_BUTTON_W 50
#define NIGHT_RIGHT_DOOR_BUTTON_H 50
#define NIGHT_RIGHT_DOOR_BUTTON_X 500
#define NIGHT_RIGHT_DOOR_BUTTON_Y 400
#define NIGHT_LEFT_LIGHT_BUTTON_W 50
#define NIGHT_LEFT_LIGHT_BUTTON_H 50
#define NIGHT_LEFT_LIGHT_BUTTON_X 150
#define NIGHT_LEFT_LIGHT_BUTTON_Y 400
#define NIGHT_RIGHT_LIGHT_BUTTON_W 50
#define NIGHT_RIGHT_LIGHT_BUTTON_H 50
#define NIGHT_RIGHT_LIGHT_BUTTON_X 400
#define NIGHT_RIGHT_LIGHT_BUTTON_Y 400

void handle_night_survival_mouse_click(GameState* state, const GameEvent* event) {
    int mouse_x = state->global_data.mouse_x;
    int mouse_y = state->global_data.mouse_y;
    if (state->data.night_survival.camera_monitor_up) {
        // If the camera monitor is up, check if the click was on a camera feed to switch to it
        if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1A_X,
            NIGHT_CAMERA_1A_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_1A;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1B_X,
            NIGHT_CAMERA_1B_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_1B;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_2A_X,
            NIGHT_CAMERA_2A_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_2A;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_2B_X,
            NIGHT_CAMERA_2B_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_2B;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_1C_X,
            NIGHT_CAMERA_1C_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_1C;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_3_X,
            NIGHT_CAMERA_3_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_3;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_4A_X,
            NIGHT_CAMERA_4A_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_4A;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_4B_X,
            NIGHT_CAMERA_4B_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)){
                
            state->data.night_survival.viewing_camera = CAM_4B;
        }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_5_X,
            NIGHT_CAMERA_5_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_5;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_6_X,
            NIGHT_CAMERA_6_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_6;
            }

        else if (is_mouse_inside(mouse_x, mouse_y,
            NIGHT_CAMERA_7_X,
            NIGHT_CAMERA_7_Y,
            BUTTON_SIZE_WIDTH,
            BUTTON_SIZE_HEIGHT)) {

            state->data.night_survival.viewing_camera = CAM_7;
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

// Helper functions for camera movement logic

// Timer for when the camera stops moving and waits before moving again in the opposite direction
/**
 * @brief Helper function to manage the waiting state when the camera is not moving in the night survival state. It increments the wait timer and checks if it has reached the defined wait time threshold (CAMERA_MOVEMENT_WAIT_TIME). If the threshold is reached, it resets the wait timer and changes the camera movement direction to the opposite of the last direction.
 * @param night_state Pointer to the NightSurvivalState struct, which contains the current state
 * of the night survival game, including the wait timer and movement direction. This function modifies the wait timer and movement direction based on the waiting logic for camera movement.
 */
static void wait_no_movement(NightSurvivalState* night_state) {
    night_state->wait_timer++;
    if (night_state->wait_timer >= CAMERA_MOVEMENT_WAIT_TIME) {
        night_state->wait_timer = 0;
        night_state->moving = (night_state->last_camera_direction == LEFT) ? RIGHT : LEFT;
    }
}

/**
 * @brief Helper function to clamp the camera movement to the rightmost position in the night survival state. It sets the camera offset to the maximum right offset (CAMERA_MAX_OFFSET), updates the last camera direction to LEFT, and sets the current movement to NO_MOVEMENT. This function is called when the camera tries to move beyond the rightmost limit, ensuring that it stays within bounds and prepares for a potential change in direction after waiting.
 * @param night_state Pointer to the NightSurvivalState struct, which contains the current state of the nighyt survival game.
 */
static void clamp_right_side(NightSurvivalState* night_state) {
    night_state->camera_offset_x = CENTER_CAMERA_OFFSET + CAMERA_MAX_OFFSET;
    night_state->last_camera_direction = LEFT;
    night_state->moving = NO_MOVEMENT;
    night_state->wait_timer = 0;
}

/**
 * @brief Helper function to clamp the camera movement to the leftmost position in the night survival state. It sets the camera offset to the maximum left offset (-CAMERA_MAX_OFFSET), updates the last camera direction to RIGHT, and sets the current movement to NO_MOVEMENT. This function is called when the camera tries to move beyond the leftmost limit, ensuring that it stays within bounds and prepares for a potential change in direction after waiting.
 * @param night_state Pointer to the NightSurvivalState struct, which contains the current state of the night survival game.
 */
static void clamp_left_side(NightSurvivalState* night_state) {
    night_state->camera_offset_x = CENTER_CAMERA_OFFSET - CAMERA_MAX_OFFSET;
    night_state->last_camera_direction = RIGHT;
    night_state->moving = NO_MOVEMENT;
    night_state->wait_timer = 0;
}



void handle_night_survival_timer(GameState* state, const GameEvent* event) {

    // Update background offset based on movement
    if (state->global_data.moving == LEFT && state->global_data.background_offset_x <= 0) {
        state->global_data.background_offset_x += BACKGROUND_MOVE_VELOCITY;
        if (state->global_data.background_offset_x > 0 || state->global_data.background_offset_x == CENTER_BACKGROUND_OFFSET) {
            state->global_data.moving = NO_MOVEMENT; // stop movement when reaching the leftmost position or the center
        }
    }
    else if (state->global_data.moving == RIGHT && state->global_data.background_offset_x >= -BACKGROUND_MAX_OFFSET) {
        state->global_data.background_offset_x -= BACKGROUND_MOVE_VELOCITY;
        if (state->global_data.background_offset_x < -BACKGROUND_MAX_OFFSET || state->global_data.background_offset_x == CENTER_BACKGROUND_OFFSET) {
            state->global_data.moving = NO_MOVEMENT;
        }
    }

    // Decrease time left
    NightSurvivalState* night_state = &state->data.night_survival;
    night_state->time_left--; // This is in ticks

    // Check if the player has survived the night
    if(night_state->time_left <= 0) {
        stop_sound();
        init_night_6am(state);
        return;
    }

    /* CAMERA ANIMATION */
    // If the camera monitor is up and the animation is playing, it means the space was pressed and the camera monitor was flipped up, so its animation should be playing forward
    if(night_state->camera_monitor_up && night_state->camera_animation_playing ) {
        // Update the animation
        animate_sprite_once(state->data.night_survival.camera_monitor);
        // Check if the animation has finished playing to reset the state (essentially finish the animation playing)
        if (state->data.night_survival.camera_monitor->is_finished) {
            state->data.night_survival.camera_animation_playing = false;
        }
    }

    if(!night_state->camera_monitor_up && night_state->camera_animation_playing) {
        animate_sprite_once_reverse(state->data.night_survival.camera_monitor);
        if (state->data.night_survival.camera_monitor->is_finished) {
            state->data.night_survival.camera_animation_playing = false;
        }
    }
    
    // Avoids when camera monitor is not up and cameras where camera feed should not move (CAM_3 and CAM_6)
    if (night_state->camera_monitor_up && night_state->viewing_camera != CAM_6 && night_state->viewing_camera != CAM_3) {
        if (night_state->moving == NO_MOVEMENT) {
            wait_no_movement(night_state);
        }
        else {
            // Move camera left is the same of moving the background right
            int step = (night_state->moving == LEFT) ? CAMERA_MOVE_VELOCITY : -CAMERA_MOVE_VELOCITY;
            int next = night_state->camera_offset_x + step;

            if (next >= CENTER_CAMERA_OFFSET + CAMERA_MAX_OFFSET) {
                clamp_right_side(night_state);
            }
            else if (next <= CENTER_CAMERA_OFFSET - CAMERA_MAX_OFFSET) {
                clamp_left_side(night_state);
            }
            else {
                night_state->camera_offset_x = next;
            }
        }
    }
    else {
        night_state->wait_timer = 0;
    }

    /* BATTERY DRAIN */
    
    // Base: accumulate 1 per tick
    int* drain_speed = &night_state->power_drain_speed;
    int* drain_rate = &night_state->power_drain_rate;

    *drain_speed = 1;
    
    // Increase the drain rate based on the what the player is using
    if (night_state->left_door_closed) *drain_speed += BATTERY_DRAIN_RATE_DOOR;
    if (night_state->right_door_closed) *drain_speed += BATTERY_DRAIN_RATE_DOOR;
    if (night_state->left_light_on) *drain_speed += BATTERY_DRAIN_RATE_LIGHT;
    if (night_state->right_light_on) *drain_speed += BATTERY_DRAIN_RATE_LIGHT;
    if (night_state->camera_monitor_up) *drain_speed += BATTERY_DRAIN_RATE_CAMERA;
    
    *drain_rate -= *drain_speed;
    
    if (night_state->power_drain_rate <= 0) {
        night_state->power_level--;
        *drain_rate = DRAIN_RATE_PER_NIGHT[state->global_data.current_night - 1] + *drain_rate; // carry over the power drained
    }

    if (night_state->power_level == 0) {
        stop_sound();
        init_night_no_battery(state);
        return;
    }
    
    /* AMIMATRONIC MOVEMENT */

    for(AnimatronicName name = 0; name < NUM_ANIMATRONICS; name++) {
        
        bool attacked = update_animatronic(
            &night_state->animatronics[name],
            night_state->time_left,
            night_state->left_door_closed,
            night_state->right_door_closed,
            night_state->camera_monitor_up,
            night_state->viewing_camera
        );

        if (attacked) {
            stop_sound();
            init_jumpscare(state, night_state->animatronics[name].name);
            return;
        }
    }
}

void handle_night_survival_keyboard(GameState* state, const GameEvent* event) {
    if(event->data.key == KEY_SPACE) {
        AnimSprite *mon = state->data.night_survival.camera_monitor;
        // Reset animation state before playing
        mon->is_finished = false;
        mon->cur_aspeed = mon->aspeed;

        if (state->data.night_survival.camera_monitor_up) {
            // The animation curent fig should be the last one (then animating in reverse)
            mon->cur_fig = mon->num_fig - 1;
        } else {
            // The other way around
            mon->cur_fig = 0;
        }
        mon->sp->map = mon->map[mon->cur_fig];
        state->data.night_survival.camera_animation_playing = true;
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

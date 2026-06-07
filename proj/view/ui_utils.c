#include "ui_utils.h"
#include "ui.h"
#include "../models/assets.h"

bool is_mouse_inside(int mouse_x, int mouse_y, int box_x, int box_y, int
box_w, int box_h) {
    return (
        mouse_x >= box_x && mouse_x <= box_x + box_w &&
        mouse_y >= box_y && mouse_y <= box_y + box_h
    );
}

/**
 * @brief Helper function to draw a sprite with its x coordinate adjusted based on the current background offset. This is used to draw sprites that are part of the office background (e.g., doors, lights) so that they move together with the background when the player moves the camera left or right.
 * @param sp The sprite to be drawn, which should be a sprite that is part of the office background and needs to be adjusted based on the background offset.
 * @param background_offset_x  The background offset in the x-direction.
 * @param original_x The original x coordinate of the sprite before adjustment. This is used to calculate the correct adjusted x coordinate based on the background offset.
 */
static void draw_left_adjusted_sprite(Sprite* sp, int background_offset_x, int original_x){
    sp->x = original_x + background_offset_x;
    draw_sprite(sp);
}

/** 
 * @brief Similar to draw_left_adjusted_sprite but for sprites on the right side of the office, which need to be adjusted differently based on the background offset to maintain their correct position relative to the background.
 * @param sp The sprite to be drawn, which should be a sprite that is part of the office background and needs to be adjusted based on the background offset.
 * @param background_offset_x The background offset in the x-direction.
 * @param original_x The original x coordinate of the sprite before adjustment. This is used to calculate the correct adjusted x coordinate based on the background offset.
 */
static void draw_right_adjusted_sprite(Sprite* sp, int background_offset_x, int original_x){
    sp->x = original_x + (background_offset_x - BACKGROUND_MAX_OFFSET);
    draw_sprite(sp);
}


static AnimatronicName check_animatronic_at_door(const NightSurvivalState* night_survival, CameraID door){
    AnimatronicName res = NUM_ANIMATRONICS; // in case of no animatronics at the door
    const Animatronic* animatronics = night_survival->animatronics;
    for(int i = 0; i < NUM_ANIMATRONICS; i++){
        if(animatronics[i].path[animatronics[i].current_position_index] == door){
            res = animatronics[i].name;
            break;
        }
    }
    return res;
}


void draw_left_door(const GameState *state) {
    const NightSurvivalState* night_survival = &state->data.night_survival;
    int background_offset_x = state->global_data.background_offset_x;
    bool is_door_closed = night_survival->left_door_closed;
    bool is_light_on = night_survival->left_light_on;
    bool is_left_door_animation_playing = night_survival->left_door_animation_playing;

    // Check animatronic for left door
    AnimatronicName animatronic_at_door = check_animatronic_at_door(night_survival, LEFT_DOOR);
    if (!is_door_closed){
        if(is_light_on){
            if(animatronic_at_door == BONNIE){
                draw_left_adjusted_sprite(get_asset(LIGHT_BONNIE_OPEN), background_offset_x, LEFT_DOOR_X);
            }
            else if(animatronic_at_door == FOXY){
                draw_left_adjusted_sprite(get_asset(LIGHT_FOXY_OPEN), background_offset_x, LEFT_DOOR_X);
            }
            else if (animatronic_at_door == NUM_ANIMATRONICS){
                draw_left_adjusted_sprite(get_asset(LIGHT_DOOR_LEFT), background_offset_x, LEFT_DOOR_X);
            }
        }
        // Nothing drawn if light is off and door is open        
    }
    else {
        if(is_light_on){
            if(animatronic_at_door == BONNIE){
                draw_left_adjusted_sprite(get_asset(LIGHT_BONNIE_CLOSED), background_offset_x, LEFT_DOOR_X);
            }
            else if(animatronic_at_door == FOXY){
                draw_left_adjusted_sprite(get_asset(LIGHT_FOXY_CLOSED), background_offset_x, LEFT_DOOR_X);
            }
            else if (animatronic_at_door == NUM_ANIMATRONICS){
                draw_left_adjusted_sprite(get_asset(LIGHT_DOOR_LEFT_CLOSED), background_offset_x, LEFT_DOOR_X);
            }
        }
        else if (!is_left_door_animation_playing){
            draw_left_adjusted_sprite(get_asset(DOOR_LEFT_CLOSED), background_offset_x, LEFT_DOOR_X);
        }
    }

    // Draw on top if animation is playing
    if(is_left_door_animation_playing){
        draw_left_adjusted_sprite(night_survival->left_door->sp, background_offset_x, LEFT_DOOR_X);
    }
}


void draw_right_door(const GameState *state) {
    const NightSurvivalState* night_survival = &state->data.night_survival;
    int background_offset_x = state->global_data.background_offset_x;
    bool is_door_closed = night_survival->right_door_closed;
    bool is_light_on = night_survival->right_light_on;
    bool is_right_door_animation_playing = night_survival->right_door_animation_playing;

    // Check animatronic for right door
    AnimatronicName animatronic_at_door = check_animatronic_at_door(night_survival, RIGHT_DOOR);
    if (!is_door_closed){
        if(is_light_on){
            if(animatronic_at_door == FREDDY){
                draw_right_adjusted_sprite(get_asset(LIGHT_FREDDY_OPEN), background_offset_x, RIGHT_DOOR_X);
            }
            else if(animatronic_at_door == CHICA){
                draw_right_adjusted_sprite(get_asset(LIGHT_CHICA_OPEN), background_offset_x, RIGHT_DOOR_X);
            }
            else if (animatronic_at_door == NUM_ANIMATRONICS){
                draw_right_adjusted_sprite(get_asset(LIGHT_DOOR_RIGHT), background_offset_x, RIGHT_DOOR_X);
            }
        }
        // Nothing drawn if light is off and door is open        
    }
    else {
        if(is_light_on){
            if(animatronic_at_door == FREDDY){
                draw_right_adjusted_sprite(get_asset(LIGHT_FREDDY_CLOSED), background_offset_x, RIGHT_DOOR_X);
            }
            else if(animatronic_at_door == CHICA){
                draw_right_adjusted_sprite(get_asset(LIGHT_CHICA_CLOSED), background_offset_x, RIGHT_DOOR_X);
            }
            else if (animatronic_at_door == NUM_ANIMATRONICS){
                draw_right_adjusted_sprite(get_asset(LIGHT_DOOR_RIGHT_CLOSED), background_offset_x, RIGHT_DOOR_X);
            }
        }
        else if (!is_right_door_animation_playing){
            draw_right_adjusted_sprite(get_asset(DOOR_RIGHT_CLOSED), background_offset_x, RIGHT_DOOR_X);
        }
    }

    // Draw on top if animation is playing
    if(is_right_door_animation_playing){
        draw_right_adjusted_sprite(night_survival->right_door->sp, background_offset_x, RIGHT_DOOR_X);
    }
}


void draw_left_door_button(const GameState *state) {
    const NightSurvivalState* night_survival = &state->data.night_survival;
    int background_offset_x = state->global_data.background_offset_x;
    if (night_survival->left_door_closed) {
        draw_left_adjusted_sprite(get_asset(LEFT_BUTTON_GREEN), background_offset_x, NIGHT_LEFT_DOOR_BUTTON_X);
    }
    else {
        draw_left_adjusted_sprite(get_asset(LEFT_BUTTON_RED), background_offset_x, NIGHT_LEFT_DOOR_BUTTON_X);
    }
}

void draw_right_door_button(const GameState *state) {
    const NightSurvivalState* night_survival = &state->data.night_survival;
    int background_offset_x = state->global_data.background_offset_x;
    if (night_survival->right_door_closed) {
        draw_right_adjusted_sprite(get_asset(RIGHT_BUTTON_GREEN), background_offset_x, NIGHT_RIGHT_DOOR_BUTTON_X);
    }
    else {
        draw_right_adjusted_sprite(get_asset(RIGHT_BUTTON_RED), background_offset_x, NIGHT_RIGHT_DOOR_BUTTON_X);
    }
}

void draw_left_light_button(const GameState *state) {
    const NightSurvivalState* night_survival = &state->data.night_survival;
    int background_offset_x = state->global_data.background_offset_x;
    if (night_survival->left_light_on) {
        draw_left_adjusted_sprite(get_asset(LIGHT_ON_LEFT), background_offset_x, NIGHT_LEFT_LIGHT_BUTTON_X);
    }
    else {
        draw_left_adjusted_sprite(get_asset(LIGHT_OFF_LEFT), background_offset_x, NIGHT_LEFT_LIGHT_BUTTON_X);
    }
}

void draw_right_light_button(const GameState *state) {
    const NightSurvivalState* night_survival = &state->data.night_survival;
    int background_offset_x = state->global_data.background_offset_x;
    if (night_survival->right_light_on) {
        draw_right_adjusted_sprite(get_asset(LIGHT_ON_RIGHT), background_offset_x, NIGHT_RIGHT_LIGHT_BUTTON_X);
    }
    else {
        draw_right_adjusted_sprite(get_asset(LIGHT_OFF_RIGHT), background_offset_x, NIGHT_RIGHT_LIGHT_BUTTON_X);
    }
}

#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"

#include <stdlib.h>

static uint8_t animatronics_at_cam(const Animatronic *animatronics, CameraID camera_id) {
    uint8_t key = 0;
    for (int i = 0; i < NUM_ANIMATRONICS; i++) {
        if (animatronics[i].path[animatronics[i].current_position_index] == camera_id)
            key |= (1 << i);
    }
    return key;
}


void draw_battery_indicator(int power_level, int power_drain_speed, int current_night) {
    draw_sprite(get_asset(POWER_LEFT));
    
    xpmASSET second_digit = power2_to_asset[power_level % 10];


    // Draw decimal digit 
    if (power_level == 100) { // assume 99% for 100%
        draw_sprite(get_asset(I_POWER9)); 
        second_digit = II_POWER9;

    } else if (power_level >= 10) {
        xpmASSET first_digit = power1_to_asset[power_level / 10];
        draw_sprite(get_asset(first_digit));
    }

    // Draw unit digit
    draw_sprite(get_asset(second_digit));
    draw_sprite(get_asset(PERCENTAGE_SIGN));
    draw_sprite(get_asset(POWER_USAGE));

    // Power consumption speed
    if (power_drain_speed == 1) {
        draw_sprite(get_asset(USAGE1));
    } else if (power_drain_speed <= 3) {
        draw_sprite(get_asset(USAGE2));
    } else if (power_drain_speed <= 5) {
        draw_sprite(get_asset(USAGE3));
    } else {
        draw_sprite(get_asset(USAGE4));
    }
}

void render_night_survival(const GameState *state) {
    if (state == NULL) return;

    const Animatronic *animatronics = state->data.night_survival.animatronics;

    if (state->data.night_survival.camera_monitor_up) {
        // Player is on cams

        const CameraID cam = state->data.night_survival.viewing_camera;
        uint8_t key = animatronics_at_cam(animatronics, cam);

        switch (cam) {
            case CAM_1A: draw_sprite(get_asset(cam1a_assets[key])); break;
            case CAM_1B: draw_sprite(get_asset(cam1b_assets[key])); break;
            case CAM_1C: draw_sprite(get_asset(cam1c_assets[key])); break;
            case CAM_2A: draw_sprite(get_asset(cam2a_assets[key])); break;
            case CAM_2B: draw_sprite(get_asset(cam2b_assets[key])); break;
            case CAM_3: draw_sprite(get_asset(cam3_assets[key])); break;
            case CAM_4A: draw_sprite(get_asset(cam4a_assets[key])); break;
            case CAM_4B: draw_sprite(get_asset(cam4b_assets[key])); break;
            case CAM_5: draw_sprite(get_asset(cam5_assets[key])); break;
            case CAM_6: draw_sprite(get_asset(cam6_assets[key])); break;
            case CAM_7: draw_sprite(get_asset(cam7_assets[key])); break;
            case LEFT_DOOR: break; //TODO: see what to draw
            case RIGHT_DOOR: break; //TODO: see what to draw 
        }
    } else {
        // Player is in office
        draw_sprite(get_asset(OFFICE));

        // Check if light is on or not.
        if (state->data.night_survival.left_door_closed) {
            draw_sprite(get_asset(LEFT_DOOR_CLOSED));
        }
        if (state->data.night_survival.right_door_closed) {
            draw_sprite(get_asset(RIGHT_DOOR_CLOSED));
        }

        for (int i = 0; i < NUM_ANIMATRONICS; i++) {
            if (animatronics[i].path[animatronics[i].current_position_index] == LEFT_DOOR) {
                // LEFT side
                if (animatronics[i].name == BONNIE) {
                    draw_sprite(get_asset(BONNIE_LEFT_DOOR));
                } else if (animatronics[i].name == FOXY) {
                    draw_sprite(get_asset(FOXY_LEFT_DOOR));
                }
            }
            if (animatronics[i].path[animatronics[i].current_position_index] == RIGHT_DOOR) {
                // RIGHT side
                if (animatronics[i].name == FREDDY) {
                    draw_sprite(get_asset(FREDDY_RIGHT_DOOR));
                } else if (animatronics[i].name == CHICA) {
                    draw_sprite(get_asset(CHICA_RIGHT_DOOR));
                }
            }
        }
    }
    draw_battery_indicator(state->data.night_survival.power_level, state->data.night_survival.power_drain_speed, state->global_data.current_night);
    draw_sprite(get_asset(CAMERA_FLIP_BUTTON));

    if (state->data.night_survival.time_left > HOUR_0) {
        draw_sprite(get_asset(HOUR_12AM));
    } else if (state->data.night_survival.time_left > HOUR_1) {
        draw_sprite(get_asset(HOUR_1AM));
    } else if (state->data.night_survival.time_left > HOUR_2) {
        draw_sprite(get_asset(HOUR_2AM));
    } else if (state->data.night_survival.time_left > HOUR_3) {
        draw_sprite(get_asset(HOUR_3AM));
    } else if (state->data.night_survival.time_left > HOUR_4) {
        draw_sprite(get_asset(HOUR_4AM));
    } else {
        draw_sprite(get_asset(HOUR_5AM));
    }

    draw_sprite(get_asset(AM_TEXT));
    
    if (state->global_data.current_night == 1) {
        draw_sprite(get_asset(NIGHT_TEXT_1));
    } else if (state->global_data.current_night == 2) {
        draw_sprite(get_asset(NIGHT_TEXT_2));
    } else if (state->global_data.current_night == 3) {
        draw_sprite(get_asset(NIGHT_TEXT_3));
    } else if (state->global_data.current_night == 4) {
        draw_sprite(get_asset(NIGHT_TEXT_4));
    } else if (state->global_data.current_night == 5) {
        draw_sprite(get_asset(NIGHT_TEXT_5));
    }
}

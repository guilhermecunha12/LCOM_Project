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

void draw_office(int background_offset_x) {
    Sprite* office_sprite = get_asset(OFFICE);
    office_sprite->x = background_offset_x;
    draw_sprite(office_sprite);
}

void draw_map(CameraID camera_id) {
    // TODO: Review this struct
    static const struct {
        int x, y;
        xpmASSET text;
        xpmASSET sel_text;
    } cam_info[] = {
        [CAM_1A] = { NIGHT_CAMERA_1A_X, NIGHT_CAMERA_1A_Y, CAM_TEXT_1A, SEL_TEXT_1A },
        [CAM_1B] = { NIGHT_CAMERA_1B_X, NIGHT_CAMERA_1B_Y, CAM_TEXT_1B, SEL_TEXT_1B },
        [CAM_2A] = { NIGHT_CAMERA_2A_X, NIGHT_CAMERA_2A_Y, CAM_TEXT_2A, SEL_TEXT_2A },
        [CAM_2B] = { NIGHT_CAMERA_2B_X, NIGHT_CAMERA_2B_Y, CAM_TEXT_2B, SEL_TEXT_2B },
        [CAM_1C] = { NIGHT_CAMERA_1C_X, NIGHT_CAMERA_1C_Y, CAM_TEXT_1C, SEL_TEXT_1C },
        [CAM_3]  = { NIGHT_CAMERA_3_X,  NIGHT_CAMERA_3_Y,  CAM_TEXT_3,  SEL_TEXT_3  },
        [CAM_4A] = { NIGHT_CAMERA_4A_X, NIGHT_CAMERA_4A_Y, CAM_TEXT_4A, SEL_TEXT_4A },
        [CAM_4B] = { NIGHT_CAMERA_4B_X, NIGHT_CAMERA_4B_Y, CAM_TEXT_4B, SEL_TEXT_4B },
        [CAM_5]  = { NIGHT_CAMERA_5_X,   NIGHT_CAMERA_5_Y,  CAM_TEXT_5,  SEL_TEXT_5  },
        [CAM_6]  = { NIGHT_CAMERA_6_X,  NIGHT_CAMERA_6_Y,  CAM_TEXT_6,  SEL_TEXT_6  },
        [CAM_7]  = { NIGHT_CAMERA_7_X,  NIGHT_CAMERA_7_Y,  CAM_TEXT_7,  SEL_TEXT_7  },
    };

    draw_sprite(get_asset(CAMS_MAP));

    Sprite *btn_active   = get_asset(CAM_BUTTON_ACTIVE);
    Sprite *btn_inactive = get_asset(CAM_BUTTON_INACTIVE);

    for (CameraID cam = CAM_1A; cam <= CAM_7; cam++) {
        bool selected = (cam == camera_id);
        Sprite *btn = selected ? btn_active : btn_inactive;
        btn->x = cam_info[cam].x;
        btn->y = cam_info[cam].y;
        draw_sprite(btn);
        draw_sprite(get_asset(cam_info[cam].text));
    }

    draw_sprite(get_asset(cam_info[camera_id].sel_text));
}

void render_night_survival(const GameState *state) {
    if (state == NULL) return;

    const Animatronic *animatronics = state->data.night_survival.animatronics;

    // Draw what the player is currently viewing (cameras)
    if (state->data.night_survival.camera_monitor_up) {
        // Player is on cams
        const CameraID cam = state->data.night_survival.viewing_camera;
        uint8_t key = animatronics_at_cam(animatronics, cam);

        Sprite* curr_sprite = NULL;

        switch (cam) {
            case CAM_1A: curr_sprite = get_asset(cam1a_assets[key]); break;
            case CAM_1B: curr_sprite = get_asset(cam1b_assets[key]); break;
            case CAM_1C: curr_sprite = get_asset(cam1c_assets[key]); break;
            case CAM_2A: curr_sprite = get_asset(cam2a_assets[key]); break;
            case CAM_2B: curr_sprite = get_asset(cam2b_assets[key]); break;
            case CAM_3: curr_sprite = get_asset(cam3_assets[key]); break;
            case CAM_4A: curr_sprite = get_asset(cam4a_assets[key]); break;
            case CAM_4B: curr_sprite = get_asset(cam4b_assets[key]); break;
            case CAM_5: curr_sprite = get_asset(cam5_assets[key]); break;
            case CAM_6: curr_sprite = get_asset(cam6_assets[key]); break;
            case CAM_7: curr_sprite = get_asset(cam7_assets[key]); break;
            case RIGHT_DOOR: break;
            case LEFT_DOOR: break;
        }

        if(curr_sprite == NULL) {
            printf("Error: No sprite found for camera %d with key %d\n", cam, key);
        }

        // Avoids cameras whose camera feed should not move (CAM_3 and CAM_6)
        if(cam != CAM_6 && cam != CAM_3) {
            curr_sprite->x = state->data.night_survival.camera_offset_x;
        }
        draw_sprite(curr_sprite);
        draw_map(cam);
    } else {
        // Player is looking at the office
        draw_office(state->global_data.background_offset_x);

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

    // Draw the animation for when the player flips the camera monitor, both up or down, in thiis case (should be "overlaid" on top of the office or camera feed)    
    if(state->data.night_survival.camera_animation_playing) {
        // The sp field of the AnimSprite struct already points to the current frame of the animation, so we can just draw it (updated by animate_sprite_once in the handlers)
        draw_sprite((Sprite*) state->data.night_survival.camera_monitor->sp);
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

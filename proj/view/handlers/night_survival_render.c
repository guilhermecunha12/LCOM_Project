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
        // Player is on office
        // how to display the correct part of the Office??
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
}

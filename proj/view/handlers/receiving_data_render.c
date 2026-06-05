#include "renderer.h"
#include "../../models/assets.h"

static Sprite* get_animatronic_asset[NUM_CAMERAS][NUM_ANIMATRONICS] = {
    [CAM_1A] = {
        [FREDDY] = get_asset(FREEDY_CAM_1A),
        [BONNIE] = get_asset(BONNIE_CAM_1A),
        [CHICA] = get_asset(CHICA_CAM_1A)
    },

    [CAM_1B] = {
        [FREDDY] = get_asset(FREEDY_CAM_1B),
        [BONNIE] = get_asset(BONNIE_CAM_1B),
        [CHICA] = get_asset(CHICA_CAM_1B)
    },

    [CAM_1C] = {
        [FOXY] = get_asset(FOXY_CAM_1C)
    },

    [CAM_2A] = {
        [BONNIE] = get_asset(BONNIE_CAM_2A),
        [FOXY] = get_asset(FOXY_CAM_2A)
    },

    [CAM_2B] = {
        [FREDDY] = get_asset(FREEDY_CAM_2B),
        [CHICA] = get_asset(CHICA_CAM_2B)
    },

    [CAM_3] = {
        [BONNIE] = get_asset(BONNIE_CAM_3)
    },

    [CAM_4A] = {
        [CHICA] = get_asset(CHICA_CAM_4A)
    },

    [CAM_4B] = {
        [FREDDY] = get_asset(FREEDY_CAM_4B),
        [CHICA] = get_asset(CHICA_CAM_4B)
    },

    [CAM_5] = {
        [BONNIE] = get_asset(BONNIE_CAM_5)
    },

    [CAM_6] = {
        [FREDDY] = get_asset(FREEDY_CAM_6),
        [CHICA] = get_asset(CHICA_CAM_6)
    },

    [CAM_7] = {
        [FREDDY] = get_asset(FREEDY_CAM_7),
        [CHICA] = get_asset(CHICA_CAM_7)
    }
};


void render_receiving_data(const GameState* state) {

    draw_sprite(get_asset(CAMERAS_OVERLAY));

    for (int cam = 0; cam < NUM_CAMERAS; cam++) {
        for (int anim = 0; anim < NUM_ANIMATRONICS; anim++) {
            if (state->data.receiving_data.animatronics_in_cam[cam][anim]) {
                draw_sprite(get_animatronic_asset[cam][anim]);
            }
        }
    }
}

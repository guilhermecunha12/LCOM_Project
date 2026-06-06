#include "renderer.h"
#include "../../models/assets.h"

static xpmASSET animatronic_asset[NUM_CAMERAS][NUM_ANIMATRONICS] = {
    [CAM_1A] = {
        [FREDDY] = FREDDY_CAM_1A,
        [BONNIE] = BONNIE_CAM_1A,
        [CHICA] = CHICA_CAM_1A
    },

    [CAM_1B] = {
        [FREDDY] = FREDDY_CAM_1B,
        [BONNIE] = BONNIE_CAM_1B,
        [CHICA] = CHICA_CAM_1B
    },

    [CAM_1C] = {
        [FOXY] = FOXY_CAM_1C
    },

    [CAM_2A] = {
        [BONNIE] = BONNIE_CAM_2A,
        [FOXY] = FOXY_CAM_2A
    },

    [CAM_2B] = {
        [FREDDY] = FREDDY_CAM_2B,
        [CHICA] = CHICA_CAM_2B,
        [FOXY] = FOXY_CAM_2B
    },

    [CAM_3] = {
        [BONNIE] = BONNIE_CAM_3
    },

    [CAM_4A] = {
        [CHICA] = CHICA_CAM_4A
    },

    [CAM_4B] = {
        [FREDDY] = FREDDY_CAM_4B,
        [CHICA] = CHICA_CAM_4B
    },

    [CAM_5] = {
        [BONNIE] = BONNIE_CAM_5
    },

    [CAM_6] = {
        [FREDDY] = FREDDY_CAM_6,
        [CHICA] = CHICA_CAM_6
    },

    [CAM_7] = {
        [FREDDY] = FREDDY_CAM_7,
        [CHICA] = CHICA_CAM_7
    },

    [RIGHT_DOOR] = {
        [FREDDY] = FREDDY_ID_RIGHT_DOOR,
        [CHICA] = CHICA_ID_RIGHT_DOOR
    },

    [LEFT_DOOR] = {
        [BONNIE] = BONNIE_ID_LEFT_DOOR,
        [FOXY] = FOXY_ID_LEFT_DOOR
    }
};

void render_receiving_data(const GameState* state) {

    draw_sprite(get_asset(MAP_SCREEN));

    for (int cam = 0; cam < NUM_CAMERAS; cam++) {
        for (int anim = 0; anim < NUM_ANIMATRONICS; anim++) {
            //if (state->data.receiving_data.animatronics_in_cam[cam][anim]) {
                draw_sprite(get_asset(animatronic_asset[cam][anim]));
            //}
        }
    }
}

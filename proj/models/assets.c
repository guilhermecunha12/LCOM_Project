// models/assets.c
#include "assets.h"
#include "sprite.h"
#include "../view/ui.h"

#include "xpm/menu/menu.xpm"
#include "xpm/cursor.xpm"
#include "xpm/menu/title.xpm"
#include "xpm/menu/newgame.xpm"
#include "xpm/menu/newgame_sel.xpm"
#include "xpm/menu/continue.xpm"
#include "xpm/menu/continue_sel.xpm"
#include "xpm/menu/custom_night.xpm"
#include "xpm/menu/night1.xpm"
#include "xpm/menu/night2.xpm"
#include "xpm/menu/night3.xpm"
#include "xpm/menu/night4.xpm"
#include "xpm/menu/night5.xpm"
#include "xpm/menu/exit_game.xpm"
#include "xpm/menu/exit_game_sel.xpm"
#include "xpm/night_start/newspaper.xpm"
#include "xpm/night_start/night1.xpm"
#include "xpm/night_start/night2.xpm"
#include "xpm/night_start/night3.xpm"
#include "xpm/night_start/night4.xpm"
#include "xpm/night_start/night5.xpm"

#include "xpm/office/office.xpm"
#include "xpm/office/ui/power_nr/0.xpm"
#include "xpm/office/ui/power_nr/1.xpm"
#include "xpm/office/ui/power_nr/2.xpm"
#include "xpm/office/ui/power_nr/3.xpm"
#include "xpm/office/ui/power_nr/4.xpm"
#include "xpm/office/ui/power_nr/5.xpm"
#include "xpm/office/ui/power_nr/6.xpm"
#include "xpm/office/ui/power_nr/7.xpm"
#include "xpm/office/ui/power_nr/8.xpm"
#include "xpm/office/ui/power_nr/9.xpm"
#include "xpm/office/ui/power_nr/percentage.xpm"

#include "xpm/office/ui/power.xpm"
#include "xpm/office/ui/usage.xpm"
#include "xpm/office/ui/power_nr/usage_1.xpm"
#include "xpm/office/ui/power_nr/usage_2.xpm"
#include "xpm/office/ui/power_nr/usage_3.xpm"
#include "xpm/office/ui/power_nr/usage_4.xpm"
#include "xpm/office/ui/flip.xpm"

#include "xpm/office/ui/1.xpm"
#include "xpm/office/ui/2.xpm"
#include "xpm/office/ui/3.xpm"
#include "xpm/office/ui/4.xpm"
#include "xpm/office/ui/5.xpm"
#include "xpm/office/ui/12.xpm"
#include "xpm/office/ui/AM.xpm"
#include "xpm/office/ui/night1.xpm"
#include "xpm/office/ui/night2.xpm"
#include "xpm/office/ui/night3.xpm"
#include "xpm/office/ui/night4.xpm"
#include "xpm/office/ui/night5.xpm"

#include "xpm/cams/monitor_anim/monitor1.xpm"
#include "xpm/cams/monitor_anim/monitor2.xpm"
#include "xpm/cams/monitor_anim/monitor3.xpm"
#include "xpm/cams/monitor_anim/monitor4.xpm"
#include "xpm/cams/monitor_anim/monitor5.xpm"
#include "xpm/cams/monitor_anim/monitor6.xpm"
#include "xpm/cams/monitor_anim/monitor7.xpm"
#include "xpm/cams/monitor_anim/monitor8.xpm"
#include "xpm/cams/monitor_anim/monitor9.xpm"
#include "xpm/cams/monitor_anim/monitor10.xpm"
#include "xpm/cams/monitor_anim/monitor11.xpm"

#include "xpm/cams/map.xpm"

#include "xpm/cams/rooms/library_lounge.xpm"
#include "xpm/cams/rooms/library_lounge_b.xpm"
#include "xpm/cams/rooms/library_lounge_bc.xpm"
#include "xpm/cams/rooms/library_lounge_bf.xpm"
#include "xpm/cams/rooms/library_lounge_c.xpm"
#include "xpm/cams/rooms/library_lounge_cf.xpm"
#include "xpm/cams/rooms/library_lounge_f.xpm"
#include "xpm/cams/rooms/library_lounge_all.xpm"

static Sprite* assets[NUM_ASSETS] = {NULL};

// Array to store animated sprites
static AnimSprite* assets_anim[NUM_ANIM_ASSETS] = {NULL};

void load_all_assets() {
    assets[MENU_BG] = create_sprite((xpm_map_t) menu_xpm, 0, 0);
    assets[CURSOR] = create_sprite((xpm_map_t) cursor_xpm, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    assets[GAME_TITLE] = create_sprite((xpm_map_t) title_xpm,GAME_TITLE_X, GAME_TITLE_Y);
    assets[OPT_NEWGAME] = create_sprite((xpm_map_t) newgame_xpm, NEW_GAME_X, NEW_GAME_Y);
    assets[OPT_NEWGAME_SEL] = create_sprite((xpm_map_t) newgame_sel_xpm,NEW_GAME_SEL_X, NEW_GAME_SEL_Y);
    assets[OPT_CONTINUE] = create_sprite((xpm_map_t) continue_xpm, CONTINUE_X, CONTINUE_Y);
    assets[OPT_CONTINUE_SEL] = create_sprite((xpm_map_t) continue_sel_xpm, CONTINUE_SEL_X, CONTINUE_SEL_Y);
    assets[OPT_EXIT] = create_sprite((xpm_map_t) exit_game_xpm, EXIT_GAME_X, EXIT_GAME_Y);
    assets[OPT_EXIT_SEL] = create_sprite((xpm_map_t) exit_game_sel_xpm, EXIT_GAME_SEL_X, EXIT_GAME_SEL_Y);
    assets[MENU_CUSTOM_NIGHT] = create_sprite((xpm_map_t) custom_night_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT1] = create_sprite((xpm_map_t) menu_night1_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT2] = create_sprite((xpm_map_t) menu_night2_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT3] = create_sprite((xpm_map_t) menu_night3_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT4] = create_sprite((xpm_map_t) menu_night4_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT5] = create_sprite((xpm_map_t) menu_night5_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);

    assets[NEWSPAPER_FEUP] = create_sprite((xpm_map_t) newspaper_xpm, 0, 0);
    assets[START_NIGHT1] = create_sprite((xpm_map_t) start_night1_xpm, SCREEN_TEXT_X, SCREEN_TEXT_Y);
    assets[START_NIGHT2] = create_sprite((xpm_map_t) start_night2_xpm, SCREEN_TEXT_X, SCREEN_TEXT_Y);
    assets[START_NIGHT3] = create_sprite((xpm_map_t) start_night3_xpm, SCREEN_TEXT_X, SCREEN_TEXT_Y);
    assets[START_NIGHT4] = create_sprite((xpm_map_t) start_night4_xpm, SCREEN_TEXT_X, SCREEN_TEXT_Y);
    assets[START_NIGHT5] = create_sprite((xpm_map_t) start_night5_xpm, SCREEN_TEXT_X, SCREEN_TEXT_Y);
    
    assets[OFFICE] = create_sprite((xpm_map_t) office_xpm, 0, 0);
    assets[I_POWER0] = create_sprite((xpm_map_t) p0_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER1] = create_sprite((xpm_map_t) p1_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER2] = create_sprite((xpm_map_t) p2_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER3] = create_sprite((xpm_map_t) p3_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER4] = create_sprite((xpm_map_t) p4_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER5] = create_sprite((xpm_map_t) p5_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER6] = create_sprite((xpm_map_t) p6_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER7] = create_sprite((xpm_map_t) p7_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER8] = create_sprite((xpm_map_t) p8_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[I_POWER9] = create_sprite((xpm_map_t) p9_xpm, I_DIGIT_POWER_X, I_DIGIT_POWER_Y);
    assets[II_POWER0] = create_sprite((xpm_map_t) p0_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER1] = create_sprite((xpm_map_t) p1_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER2] = create_sprite((xpm_map_t) p2_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER3] = create_sprite((xpm_map_t) p3_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER4] = create_sprite((xpm_map_t) p4_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER5] = create_sprite((xpm_map_t) p5_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER6] = create_sprite((xpm_map_t) p6_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER7] = create_sprite((xpm_map_t) p7_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER8] = create_sprite((xpm_map_t) p8_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[II_POWER9] = create_sprite((xpm_map_t) p9_xpm, II_DIGIT_POWER_X, II_DIGIT_POWER_Y);
    assets[PERCENTAGE_SIGN] = create_sprite((xpm_map_t) percentage_xpm, PERCENTAGE_SIGN_X, PERCENTAGE_SIGN_Y);
    assets[POWER_LEFT] = create_sprite((xpm_map_t) power_xpm, POWER_LEFT_TEXT_X, POWER_LEFT_TEXT_Y);
    assets[POWER_USAGE] = create_sprite((xpm_map_t) usage_xpm, USAGE_TEXT_X, USAGE_TEXT_Y);
    assets[USAGE1] = create_sprite((xpm_map_t) usage_1_xpm, INDICATOR_USAGE_X, INDICATOR_USAGE_Y);
    assets[USAGE2] = create_sprite((xpm_map_t) usage_2_xpm, INDICATOR_USAGE_X, INDICATOR_USAGE_Y);
    assets[USAGE3] = create_sprite((xpm_map_t) usage_3_xpm, INDICATOR_USAGE_X, INDICATOR_USAGE_Y);
    assets[USAGE4] = create_sprite((xpm_map_t) usage_4_xpm, INDICATOR_USAGE_X, INDICATOR_USAGE_Y);

    assets[CAMERA_FLIP_BUTTON] = create_sprite((xpm_map_t) flip_xpm, CAMERA_FLIP_BUTTON_X, CAMERA_FLIP_BUTTON_Y);
    assets[HOUR_12AM] = create_sprite((xpm_map_t) h12_xpm, NIGHT_HOURS_TEXT_X, NIGHT_HOURS_TEXT_Y);
    assets[HOUR_1AM] = create_sprite((xpm_map_t) h1_xpm, NIGHT_HOURS_TEXT_X, NIGHT_HOURS_TEXT_Y);
    assets[HOUR_2AM] = create_sprite((xpm_map_t) h2_xpm, NIGHT_HOURS_TEXT_X, NIGHT_HOURS_TEXT_Y);
    assets[HOUR_3AM] = create_sprite((xpm_map_t) h3_xpm, NIGHT_HOURS_TEXT_X, NIGHT_HOURS_TEXT_Y);
    assets[HOUR_4AM] = create_sprite((xpm_map_t) h4_xpm, NIGHT_HOURS_TEXT_X, NIGHT_HOURS_TEXT_Y);
    assets[HOUR_5AM] = create_sprite((xpm_map_t) h5_xpm, NIGHT_HOURS_TEXT_X, NIGHT_HOURS_TEXT_Y);
    assets[AM_TEXT] = create_sprite((xpm_map_t) AM_xpm, AM_TEXT_X, AM_TEXT_Y);

    assets[NIGHT_TEXT_1] = create_sprite((xpm_map_t) night1_xpm, NIGHT_COUNT_TEXT_X, NIGHT_COUNT_TEXT_Y);
    assets[NIGHT_TEXT_2] = create_sprite((xpm_map_t) night2_xpm, NIGHT_COUNT_TEXT_X, NIGHT_COUNT_TEXT_Y);
    assets[NIGHT_TEXT_3] = create_sprite((xpm_map_t) night3_xpm, NIGHT_COUNT_TEXT_X, NIGHT_COUNT_TEXT_Y);
    assets[NIGHT_TEXT_4] = create_sprite((xpm_map_t) night4_xpm, NIGHT_COUNT_TEXT_X, NIGHT_COUNT_TEXT_Y);
    assets[NIGHT_TEXT_5] = create_sprite((xpm_map_t) night5_xpm, NIGHT_COUNT_TEXT_X, NIGHT_COUNT_TEXT_Y);

    assets[CAM_1A_EMPTY] = create_sprite((xpm_map_t) library_lounge_xpm, 0, 0);
    assets[CAM_1A_FREDDY] = create_sprite((xpm_map_t) library_lounge_f_xpm, 0, 0);
    assets[CAM_1A_BONNIE] = create_sprite((xpm_map_t) library_lounge_b_xpm, 0, 0);
    assets[CAM_1A_CHICA] = create_sprite((xpm_map_t) library_lounge_c_xpm, 0, 0);
    assets[CAM_1A_BONNIE_CHICA] = create_sprite((xpm_map_t) library_lounge_bc_xpm, 0, 0);
    assets[CAM_1A_FREDDY_BONNIE] = create_sprite((xpm_map_t) library_lounge_bf_xpm, 0, 0);
    assets[CAM_1A_FREDDY_BONNIE_CHICA] = create_sprite((xpm_map_t) library_lounge_all_xpm, 0, 0);

    assets[CAMS_MAP] = create_sprite((xpm_map_t) map_xpm, MAP_LAYOUT_X, MAP_LAYOUT_Y);

    // Here we load the animated sprites, with all needed data: number of frames, position, speed and all xpm's needed
    assets_anim[ANIM_CAMERA_MONITOR] = create_anim_sprite(11, 0, 0, TICKS_PER_CAMERA_ANIMATION_FRAME,
    (xpm_map_t) monitor1_xpm, (xpm_map_t) monitor2_xpm, (xpm_map_t) monitor3_xpm, 
    (xpm_map_t) monitor4_xpm, (xpm_map_t) monitor5_xpm, (xpm_map_t) monitor6_xpm, 
    (xpm_map_t) monitor7_xpm, (xpm_map_t) monitor8_xpm, (xpm_map_t) monitor9_xpm, 
    (xpm_map_t) monitor10_xpm, (xpm_map_t) monitor11_xpm); 
}

void unload_all_assets() {
    for (int i = 0; i < NUM_ASSETS; i++) {
        destroy_sprite(assets[i]);
        assets[i] = NULL;
    }

    // Add a new loop to destroy the animated sprites as well
    for (int i = 0; i < NUM_ANIM_ASSETS; i++) {
        destroy_anim_sprite(assets_anim[i]);
        assets_anim[i] = NULL;
    }
}

Sprite* get_asset(xpmASSET asset) {
    if (asset >= NUM_ASSETS) return NULL;
    return assets[asset];
}

AnimSprite* get_anim_asset(AnimAsset asset) {
    if (asset >= NUM_ANIM_ASSETS) return NULL;
    return assets_anim[asset];
}

int get_jumpscare_frame_count(AnimatronicName anim, bool is_freddy_lightout) {
    switch (anim) {
        case FREDDY: return is_freddy_lightout ? NUM_JUMPSCARE_FREDDY_LIGHTOUT : NUM_JUMPSCARE_FREDDY_NORMAL;
        case BONNIE: return NUM_JUMPSCARE_BONNIE;
        case CHICA: return NUM_JUMPSCARE_CHICA;
        case FOXY: return NUM_JUMSCARE_FOXY;
        default: return 0;
    }
}

xpmASSET get_jumpscare_asset(AnimatronicName anim, bool is_freddy_lightout, int frame) {
    switch (anim) {
        case FREDDY: return (xpmASSET)((is_freddy_lightout ? JUMPSCARE_FREDDY_LIGHTOUT_FIRST : JUMPSCARE_FREDDY_FIRST) + frame);
        case BONNIE: return (xpmASSET)(JUMPSCARE_BONNIE_FIRST + frame);
        case CHICA: return (xpmASSET)(JUMPSCARE_CHICA_FIRST + frame);
        case FOXY: return (xpmASSET)(JUMPSCARE_FOXY_FIRST + frame);
        default: return MENU_BG; //TODO: check this
    }
}


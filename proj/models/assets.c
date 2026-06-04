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

#include "xpm/cams/cam_button_active.xpm"
#include "xpm/cams/cam_button_inactive.xpm"

#include "xpm/cams/cam_texts/CAM1A.xpm"
#include "xpm/cams/cam_texts/CAM1B.xpm"
#include "xpm/cams/cam_texts/CAM1C.xpm"
#include "xpm/cams/cam_texts/CAM2A.xpm"
#include "xpm/cams/cam_texts/CAM2B.xpm"
#include "xpm/cams/cam_texts/CAM3.xpm"
#include "xpm/cams/cam_texts/CAM4A.xpm"
#include "xpm/cams/cam_texts/CAM4B.xpm"
#include "xpm/cams/cam_texts/CAM5.xpm"
#include "xpm/cams/cam_texts/CAM6.xpm"
#include "xpm/cams/cam_texts/CAM7.xpm"

// Rename conflicting selected-text XPMs (same var name as room XPMs)
#define library_lounge_xpm    sel_library_lounge_xpm
#include "xpm/cams/cam_texts/selected/library_lounge.xpm"
#undef library_lounge_xpm

#define computer_room_xpm     sel_computer_room_xpm
#include "xpm/cams/cam_texts/selected/computer_room.xpm"
#undef computer_room_xpm

#define council_chamber_xpm   sel_council_chamber_xpm
#include "xpm/cams/cam_texts/selected/council_chamber.xpm"
#undef council_chamber_xpm

#define east_hall_xpm         sel_east_hall_xpm
#include "xpm/cams/cam_texts/selected/east_hall.xpm"
#undef east_hall_xpm

#define east_hall_corner_xpm  sel_east_hall_corner_xpm
#include "xpm/cams/cam_texts/selected/east_hall_corner.xpm"
#undef east_hall_corner_xpm

#define lecture_hallway_xpm   sel_lecture_hallway_xpm
#include "xpm/cams/cam_texts/selected/lecture_hallway.xpm"
#undef lecture_hallway_xpm

#define locker_room_xpm       sel_locker_room_xpm
#include "xpm/cams/cam_texts/selected/locker_room.xpm"
#undef locker_room_xpm

#define west_hall_xpm         sel_west_hall_xpm
#include "xpm/cams/cam_texts/selected/west_hall.xpm"
#undef west_hall_xpm

#define west_hall_corner_xpm  sel_west_hall_corner_xpm
#include "xpm/cams/cam_texts/selected/west_hall_corner.xpm"
#undef west_hall_corner_xpm

// Non-conflicting selected texts
#include "xpm/cams/cam_texts/selected/auditorium.xpm"
#include "xpm/cams/cam_texts/selected/lcom_lab.xpm"

#include "xpm/cams/rooms/library_lounge.xpm"
#include "xpm/cams/rooms/library_lounge_b.xpm"
#include "xpm/cams/rooms/library_lounge_bc.xpm"
#include "xpm/cams/rooms/library_lounge_bf.xpm"
#include "xpm/cams/rooms/library_lounge_c.xpm"
#include "xpm/cams/rooms/library_lounge_cf.xpm"
#include "xpm/cams/rooms/library_lounge_f.xpm"
#include "xpm/cams/rooms/library_lounge_all.xpm"

#include "xpm/cams/rooms/computer_room.xpm"
#include "xpm/cams/rooms/computer_room_bonnie.xpm"
#include "xpm/cams/rooms/computer_room_chica.xpm"
#include "xpm/cams/rooms/computer_room_bonnie_chica.xpm"

#include "xpm/cams/rooms/the_auditorium.xpm"
#include "xpm/cams/rooms/auditorium_stage_2.xpm"

#include "xpm/cams/rooms/locker_room.xpm"
#include "xpm/cams/rooms/locker_room_bonnie.xpm"

#include "xpm/cams/rooms/council_chamber.xpm"
#include "xpm/cams/rooms/council_chamber_bonnie_close.xpm"

#include "xpm/cams/rooms/lecture_hallway.xpm"
#include "xpm/cams/rooms/lecture_hallway_chica.xpm"

#include "xpm/cams/rooms/west_hall.xpm"
#include "xpm/cams/rooms/west_hall_bonnie.xpm"

#include "xpm/cams/rooms/west_hall_corner.xpm"

#include "xpm/cams/rooms/east_hall.xpm"
#include "xpm/cams/rooms/east_hall_chica.xpm"

#include "xpm/cams/rooms/east_hall_corner.xpm"
#include "xpm/cams/rooms/east_hall_corner_freddy.xpm"
#include "xpm/cams/rooms/east_hall_corner_chica.xpm"

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

    assets[CAM_1B_EMPTY] = create_sprite((xpm_map_t) computer_room_xpm, 0, 0);
    assets[CAM_1B_BONNIE] = create_sprite((xpm_map_t) computer_room_bonnie_xpm, 0, 0);
    assets[CAM_1B_CHICA] = create_sprite((xpm_map_t) computer_room_chica_xpm, 0, 0);
    assets[CAM_1B_BONNIE_CHICA] = create_sprite((xpm_map_t) computer_room_bonnie_chica_xpm, 0, 0);

    assets[CAM_1C_EMPTY] = create_sprite((xpm_map_t) the_auditorium_xpm, 0, 0);
    assets[CAM_1C_FOXY] = create_sprite((xpm_map_t) auditorium_stage_2_xpm, 0, 0);

    assets[CAM_2A_EMPTY] = create_sprite((xpm_map_t) west_hall_xpm, 0, 0);
    assets[CAM_2A_BONNIE] = create_sprite((xpm_map_t) west_hall_bonnie_xpm, 0, 0);

    assets[CAM_2B_EMPTY] = create_sprite((xpm_map_t) west_hall_corner_xpm, 0, 0);

    assets[CAM_3_EMPTY] = create_sprite((xpm_map_t) locker_room_xpm, 0, 0);
    assets[CAM_3_BONNIE] = create_sprite((xpm_map_t) locker_room_bonnie_xpm, 0, 0);

    assets[CAM_4A_EMPTY] = create_sprite((xpm_map_t) east_hall_xpm, 0, 0);
    assets[CAM_4A_CHICA] = create_sprite((xpm_map_t) east_hall_chica_xpm, 0, 0);

    assets[CAM_4B_EMPTY] = create_sprite((xpm_map_t) east_hall_corner_xpm, 0, 0);
    assets[CAM_4B_FREDDY] = create_sprite((xpm_map_t) east_hall_corner_freddy_xpm, 0, 0);
    assets[CAM_4B_CHICA] = create_sprite((xpm_map_t) east_hall_corner_chica_xpm, 0, 0);

    assets[CAM_5_EMPTY] = create_sprite((xpm_map_t) council_chamber_xpm, 0, 0);
    assets[CAM_5_BONNIE] = create_sprite((xpm_map_t) council_chamber_bonnie_close_xpm, 0, 0);

    assets[CAM_7_EMPTY] = create_sprite((xpm_map_t) lecture_hallway_xpm, 0, 0);
    assets[CAM_7_CHICA] = create_sprite((xpm_map_t) lecture_hallway_chica_xpm, 0, 0);

    assets[CAM_BUTTON_ACTIVE]   = create_sprite((xpm_map_t) cam_button_active_xpm,   0, 0);
    assets[CAM_BUTTON_INACTIVE] = create_sprite((xpm_map_t) cam_button_inactive_xpm, 0, 0);

    assets[CAM_TEXT_1A] = create_sprite((xpm_map_t) CAM1A_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_1A_X, NIGHT_CAMERA_1A_Y));
    assets[CAM_TEXT_1B] = create_sprite((xpm_map_t) CAM1B_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_1B_X, NIGHT_CAMERA_1B_Y));
    assets[CAM_TEXT_1C] = create_sprite((xpm_map_t) CAM1C_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_1C_X, NIGHT_CAMERA_1C_Y));
    assets[CAM_TEXT_2A] = create_sprite((xpm_map_t) CAM2A_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_2A_X, NIGHT_CAMERA_2A_Y));
    assets[CAM_TEXT_2B] = create_sprite((xpm_map_t) CAM2B_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_2B_X, NIGHT_CAMERA_2B_Y));
    assets[CAM_TEXT_3]  = create_sprite((xpm_map_t) CAM3_xpm,  NIGHT_TEXT_POS(NIGHT_CAMERA_3_X,  NIGHT_CAMERA_3_Y));
    assets[CAM_TEXT_4A] = create_sprite((xpm_map_t) CAM4A_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_4A_X, NIGHT_CAMERA_4A_Y));
    assets[CAM_TEXT_4B] = create_sprite((xpm_map_t) CAM4B_xpm, NIGHT_TEXT_POS(NIGHT_CAMERA_4B_X, NIGHT_CAMERA_4B_Y));
    assets[CAM_TEXT_5]  = create_sprite((xpm_map_t) CAM5_xpm,  NIGHT_TEXT_POS(NIGH_CAMERA_5_X,   NIGHT_CAMERA_5_Y));
    assets[CAM_TEXT_6]  = create_sprite((xpm_map_t) CAM6_xpm,  NIGHT_TEXT_POS(NIGHT_CAMERA_6_X,  NIGHT_CAMERA_6_Y));
    assets[CAM_TEXT_7]  = create_sprite((xpm_map_t) CAM7_xpm,  NIGHT_TEXT_POS(NIGHT_CAMERA_7_X,  NIGHT_CAMERA_7_Y));

    assets[SEL_TEXT_1A] = create_sprite((xpm_map_t) sel_library_lounge_xpm,    SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_1B] = create_sprite((xpm_map_t) sel_computer_room_xpm,     SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_1C] = create_sprite((xpm_map_t) auditorium_xpm,            SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_2A] = create_sprite((xpm_map_t) sel_west_hall_xpm,         SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_2B] = create_sprite((xpm_map_t) sel_west_hall_corner_xpm,  SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_3]  = create_sprite((xpm_map_t) sel_locker_room_xpm,       SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_4A] = create_sprite((xpm_map_t) sel_east_hall_xpm,         SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_4B] = create_sprite((xpm_map_t) sel_east_hall_corner_xpm,  SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_5]  = create_sprite((xpm_map_t) sel_council_chamber_xpm,   SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_6]  = create_sprite((xpm_map_t) lcom_lab_xpm,              SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);
    assets[SEL_TEXT_7]  = create_sprite((xpm_map_t) sel_lecture_hallway_xpm,   SELECTED_CAM_TEXT_X, SELECTED_CAM_TEXT_Y);

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


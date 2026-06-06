#include "state.h"
#include "models/assets.h"
#include "view/ui.h"
#include "sound.h"
#include "devices/serial_port/serial_port.h"
#include "devices/serial_port/sp_encoding.h"
#include "controller/handlers/processor.h"

void init_main_menu(GameState* state) {
    int current_night = state->global_data.current_night;
    MainMenuState main_menu_state;
    main_menu_state.selected_option = 0;

    int num_options = (current_night == 0) ? 2 : 3;
    main_menu_state.options = (MainMenuOption*) malloc(sizeof(MainMenuOption) * (num_options + 1));

    if (current_night == 0) {
        main_menu_state.num_options = 2;
        main_menu_state.options[0] = NO_OPTION;
        main_menu_state.options[1] = NEW_GAME;
        main_menu_state.options[2] = EXIT_GAME;
    } else {
        main_menu_state.num_options = 3;
        main_menu_state.options[0] = NO_OPTION;
        main_menu_state.options[1] = NEW_GAME;
        main_menu_state.options[2] = CONTINUE;
        main_menu_state.options[3] = EXIT_GAME;
    }

    state->type = MAIN_MENU;
    state->data.main_menu = main_menu_state;
}

void init_jumpscare(GameState* state, AnimatronicName animatronic_name) {
    send_sp_data(ENDED_NIGHT_SURVIVAL);
    JumpscareState jumpscare_state;
    switch (animatronic_name) {
        case BONNIE:
            jumpscare_state.jumpscare_sprite = get_anim_asset(ANIM_BONNIE_JUMPSCARE);
            break;
        case CHICA:
            jumpscare_state.jumpscare_sprite = get_anim_asset(ANIM_CHICA_JUMPSCARE);
            break;
        case FREDDY:
            jumpscare_state.jumpscare_sprite = get_anim_asset(ANIM_FREDDY_JUMPSCARE);
            break;
        case FOXY:
            jumpscare_state.jumpscare_sprite = get_anim_asset(ANIM_FOXY_JUMPSCARE);
            break;
        default:
            jumpscare_state.jumpscare_sprite = NULL;
            break;
    }

    // Reset animation state before playing
    AnimSprite* js = jumpscare_state.jumpscare_sprite;
    js->is_finished = false;
    js->cur_aspeed = js->aspeed;
    js->cur_fig = 0;
    js->sp->map = js->map[js->cur_fig];

    jumpscare_state.animatronic_name = animatronic_name;

    state->type = JUMPSCARE;
    state->data.jumpscare = jumpscare_state;
    play_sound("jumpscare");
}

void init_night_intro(GameState* state) {
    NightIntroState night_intro_state;
    night_intro_state.duration = NIGHT_INTRO_DURATION;

    state->type = NIGHT_INTRO;
    state->data.night_intro = night_intro_state;
}

void init_newspaper(GameState* state) {
    NewspaperState newspaper_state;
    newspaper_state.duration = NEWSPAPER_DURATION;

    state->type = NEWSPAPER;
    state->data.newspaper = newspaper_state;
}
void init_night_survival(GameState* state) {
    state->type = NIGHT_SURVIVAL;
    state->global_data.background_offset_x = CENTER_BACKGROUND_OFFSET;
    state->global_data.moving = NO_MOVEMENT;

    NightSurvivalState* night_survival_state = &state->data.night_survival;
    night_survival_state->time_left = NIGHT_TIME;
    night_survival_state->power_level = DEFAULT_POWER_LEVEL;
    night_survival_state->power_drain_rate = DRAIN_RATE_PER_NIGHT[state->global_data.current_night - 1];
    night_survival_state->power_drain_speed = 1;
    night_survival_state->left_light_on = false;
    night_survival_state->right_light_on = false;
    night_survival_state->left_door_closed = false;
    night_survival_state->right_door_closed = false;
    night_survival_state->left_door_animation_playing = false;
    night_survival_state->right_door_animation_playing = false;
    night_survival_state->left_door = get_anim_asset(ANIM_DOOR_LEFT);
    night_survival_state->right_door = get_anim_asset(ANIM_DOOR_RIGHT);
    night_survival_state->camera_monitor_up = false;
    night_survival_state->camera_animation_playing = false;
    night_survival_state->camera_monitor = get_anim_asset(ANIM_CAMERA_MONITOR);
    night_survival_state->viewing_camera = CAM_1A;
    night_survival_state->fan_frame_index = 0;
    night_survival_state->static_animation_timer = 0;
    night_survival_state->camera_offset_x = CENTER_CAMERA_OFFSET;
    night_survival_state->moving = RIGHT;
    night_survival_state->wait_timer = 0;

    initialize_animatronics(night_survival_state->animatronics, state->global_data.current_night);
    play_sound("night_music");
}

void init_night_6am(GameState* state) {
    send_sp_data(ENDED_NIGHT_SURVIVAL);
    Night6AMScreen night_6am_state;
    night_6am_state.frame_index = 0;
    night_6am_state.tick_timer = 0;
    night_6am_state.duration = NIGHT_6AM_DURATION;

    state->type = NIGHT_6AM;
    state->data.night_6am = night_6am_state;

    play_sound("6am");
}

void init_night_no_battery(GameState* state) {
    int duration = state->data.night_survival.time_left;
    NightNoBatteryState night_no_battery_state;
    night_no_battery_state.time_left = duration;
    night_no_battery_state.phase1_duration = NO_BATTERY_PHASE_DURATION;
    night_no_battery_state.phase2_duration = NO_BATTERY_PHASE_DURATION;
    night_no_battery_state.freddy = initialize_freddy_no_battery();

    state->type = NIGHT_NO_BATTERY;
    state->data.night_no_battery = night_no_battery_state;
    
    play_sound("lights_out");
}

void init_win_screen(GameState* state) {
    WinState win_state;
    win_state.duration = WIN_SCREEN_DURATION;

    state->type = WIN;
    state->data.win = win_state;
}

void init_static_screen(GameState* state) {
    StaticScreenState static_screen_state;
    static_screen_state.duration = STATIC_SCREEN_DURATION;
    static_screen_state.static_sprite = get_anim_asset(ANIM_STATIC_SCREEN);

    state->type = STATIC_SCREEN;
    state->data.static_screen = static_screen_state;
}

void init_game_over(GameState* state) {
    GameOverState game_over_state;
    game_over_state.duration = GAME_OVER_DURATION;

    state->type = GAME_OVER;
    state->data.game_over = game_over_state;
}

void init_receiving_data_state(GameState* state, Queue* data_queue) {
    state->type = RECEIVING_DATA;

    // Initialize the animatronics in cam data to false
    for (int cam = 0; cam < NUM_CAMERAS; cam++) {
        for (int anim = 0; anim < NUM_ANIMATRONICS; anim++) {
            state->data.receiving_data.animatronics_in_cam[cam][anim] = false;
        }
    }

    // Initialize the current cam of each animatronic to NUM_CAMERAS (sentinel)
    for (int anim = 0; anim < NUM_ANIMATRONICS; anim++) {
        state->data.receiving_data.animatronic_current_cam[anim] = NUM_CAMERAS;
    }

    process_animatronic_movements(state, data_queue); // for the initial animatronic data
}

#include "state.h"
#include "models/assets.h"
#include "view/ui.h"


MainMenuState init_main_menu(int current_night) {
    MainMenuState state;
    state.selected_option = 0; // No option selected by default
    int num_options = (current_night == 0) ? 2 : 3; // Determine number of options based on current night
    state.options = (MainMenuOption*) malloc(sizeof(MainMenuOption) * (num_options + 1));
    if (current_night == 0) {
        state.num_options = 2;
        state.options[0] = NO_OPTION; // Placeholder for no selection
        state.options[1] = NEW_GAME;
        state.options[2] = EXIT_GAME;
    } else {
        state.num_options = 3;
        state.options[0] = NO_OPTION; // Placeholder for no selection
        state.options[1] = NEW_GAME;
        state.options[2] = CONTINUE;
        state.options[3] = EXIT_GAME;
    }
    return state;
}


JumpscareState init_jumpscare(AnimatronicName animatronic_name, bool freddy_lights_out) {
    JumpscareState state;
    state.frame_index = 0;
    state.tick_timer = 0;
    state.animatronic_name = animatronic_name;
    state.is_freddy_lightout = freddy_lights_out;
    return state;
}

void init_night_intro(GameState* state) {
    NightIntroState night_intro_state;

    // TODO: Check this frames values
    night_intro_state.frame_index = 0;
    night_intro_state.tick_timer = 0;
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

    NightSurvivalState* ns = &state->data.night_survival;
    ns->time_left = NIGHT_TIME;
    ns->power_level = DEFAULT_POWER_LEVEL;
    ns->power_drain_rate = DRAIN_RATE_PER_NIGHT[state->global_data.current_night - 1];
    ns->power_drain_speed = 1;
    ns->camera_monitor_up = false;
    ns->camera_animation_playing = false;
    ns->viewing_camera = CAM_1A;
    ns->left_light_on = false;
    ns->right_light_on = false;
    ns->left_door_closed = false;
    ns->right_door_closed = false;
    ns->camera_monitor = get_anim_asset(ANIM_CAMERA_MONITOR);
    ns->fan_frame_index = 0;
    ns->static_animation_timer = 0;

    initialize_animatronics(ns->animatronics, state->global_data.current_night);
}

Night6AMScreen init_night_6am() {
    Night6AMScreen state;
    state.frame_index = 0;
    state.tick_timer = 0;
    state.duration = NIGHT_6AM_DURATION;
    return state;
}

NightNoBatteryState init_night_no_battery(int duration) {
    NightNoBatteryState state;
    state.time_left = duration;
    state.phase1_duration = NO_BATTERY_PHASE_DURATION;
    state.phase2_duration = NO_BATTERY_PHASE_DURATION;
    state.freddy = initialize_freddy_no_battery();
    return state;
}

WinState init_win_screen() {
    WinState state;
    state.duration = WIN_SCREEN_DURATION;
    return state;
}

StaticScreenState init_static_screen() {
    StaticScreenState state;
    state.frame_index = 0;
    state.tick_timer = 0;
    state.duration = STATIC_SCREEN_DURATION;
    return state;
}

#include "state.h"


MainMenuState init_main_menu(int current_night) {
    MainMenuState state;
    state.selected_option = NO_OPTION; // No option selected
    return state;
}


JumpscareState init_jumpscare(AnimatronicName animatronic_name) {
    JumpscareState state;
    state.frame_index = 0;
    state.tick_timer = 0;
    state.animatronic_name = animatronic_name;
    return state;
}

NightIntroState init_night_intro() {
    NightIntroState state;

    // TODO: Check this frames values
    state.frame_index = 0;
    state.tick_timer = 0;

    state.duration = NIGHT_INTRO_DURATION;
    return state;
}

NightSurvivalState init_night_survival(int current_night) {
    NightSurvivalState state;
    state.time_left = NIGHT_TIME;
    state.power_level = DEFAULT_POWER_LEVEL;
    state.power_drain_rate = DRAIN_RATE_PER_NIGHT[current_night - 1];
    state.power_drain_speed = 1;

    state.left_light_on = false;
    state.right_light_on = false;
    state.left_door_closed = false;
    state.right_door_closed = false;
    state.camera_monitor_up = false;
    // TODO: Check this value, it should be a default cam
    state.viewing_camera = CAM_1A;

    // TODO: Check this frames values
    state.fan_frame_index = 0;
    state.static_animation_timer = 0;

    initialize_animatronics(state.animatronics, current_night);
    
    return state;
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

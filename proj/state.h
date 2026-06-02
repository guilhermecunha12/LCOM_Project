#ifndef STATE_H
#define STATE_H

#include "../lab4/mouse.h"
#include "models/animatronic.h"
#include "game_constants.h"

#include <stdbool.h>

typedef enum {
    TIMER_TICK,
    MOUSE_LB_CLICK,
    MOUSE_MOVE,
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
    NUM_EVENTS
} EventType;

typedef enum {
    KEY_MENU_UP,
    KEY_MENU_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_SPACE,
    KEY_ESCAPE,
    KEY_INVALID,
} Key;

// Tagged Union - TODO: instead of scancodes and mouse_packets, have enums that represent the keys
typedef struct {
    EventType type;
    union { // TODO: simplify this structs if only one field is needed for each event type
        Key key;
        struct {int16_t delta_x; int16_t delta_y;} mouse_coords;
        int timer_ticks;
    } data;
} GameEvent;

// Game states
typedef enum {
    MAIN_MENU,
    NIGHT_INTRO,
    NIGHT_SURVIVAL,
    NIGHT_6AM, // E.g., The "6 AM! Next Night" screen
    JUMPSCARE,
    NIGHT_NO_BATTERY, // countdown to possible Freedie jumpscare (PHASE 1: every 5 seconds, 20% chance of jumpscare. If there is a jumpscare, the night ends. Otherwise, after 4 failed tries, go to PHASE 2: every 2 seconds, 20% chance of jumpscare, max 20 seconds (10 tries). If those 10 tries fail, jumpscare guaranteed and night ends. If 6AM is reached, independent of the phase, the  night ends and the player passes the night)
    WIN,
    STATIC_SCREEN,
    GAME_OVER,
    EXIT,
    NUM_STATES
} StateType;

// Global game data that persists across states
typedef struct {
    int current_night; // 0 (no current night), 1 to 5 - also used to determine night's gimmicks

    // mouse coordinates for displaying it
    int mouse_x;
    int mouse_y;

    // Shared data for states that have camera movement (e.g., night survival and night no battery)
    int background_offset_x;
} PersistentData;

typedef enum {
    NO_OPTION,
    NEW_GAME,
    CONTINUE,
    EXIT_GAME,
    NUM_OPTIONS
} MainMenuOption;

typedef struct {
    MainMenuOption selected_option; // for keyboard navigation in main menu; 0 for no option selected
} MainMenuState;

typedef struct {
    int frame_index;
    int tick_timer;
    int duration;
} NightIntroState;

typedef struct {
    int time_left;

    int power_level; // 100 - 0
    int power_drain_rate; // number of ticks needed to decrement power by 1 unit
    int power_drain_accumulator;

    bool left_light_on;
    bool right_light_on;
    bool left_door_closed;
    bool right_door_closed;
    bool camera_monitor_up; // Is the player looking at cameras?
    CameraID viewing_camera;

    // For timer-driven animations (e.g., fan spinning, camera static)
    int fan_frame_index;
    int static_animation_timer;

    Animatronic animatronics[NUM_ANIMATRONICS]; // Metadata for each animatronic
} NightSurvivalState;

typedef struct {
    int time_left;
    int phase1_duration;
    int phase2_duration;
    Animatronic freddy;
} NightNoBatteryState;

// Specific data for a sequence of changing images without player input
typedef struct {
    int frame_index; // Which frame of the jumpscare animation
    int tick_timer; // Counter to control animation speedw
    int duration;
    AnimatronicName animatronic_name; // Which character is jumpscaring?
} JumpscareState;

typedef struct {
    int frame_index;
    int tick_timer;
    int duration;
} Night6AMScreen;

typedef struct {
    int frame_index; // Which frame of the static screen animation
    int tick_timer; // Counter to control animation speed
    int duration; // Counter to control how long the static screen is displayed
} StaticScreenState;

typedef struct {
    int duration; // Counter to control how long the win screen is displayed
} WinState;

// Tagged Union to represent the current game state
typedef struct {
    PersistentData global_data; // Global data across all states
    StateType type; // tag
    union {
        MainMenuState main_menu;
        NightIntroState night_intro;
        NightSurvivalState night_survival;
        JumpscareState jumpscare;
        Night6AMScreen night_6am;
        NightNoBatteryState night_no_battery;
        WinState win;
        StaticScreenState static_screen;
    } data; // state-specific data
} GameState;

/* Initializers */

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
    state.power_drain_accumulator = 0;

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

    Animatronic animatronics[NUM_ANIMATRONICS];
    initialize_animatronics(animatronics, current_night);

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

#endif /* STATE_H */

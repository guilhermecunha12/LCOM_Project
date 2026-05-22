#ifndef STATE_H
#define STATE_H

#include "../lab4/mouse.h"
#include "models/animatronic.h"

#define HOUR_0 GAME_TIME - 4628 * 1
#define HOUR_1 GAME_TIME - 4628 * 2
#define HOUR_2 GAME_TIME - 4628 * 3
#define HOUR_3 GAME_TIME - 4628 * 4
#define HOUR_4 GAME_TIME - 4628 * 5
#define HOUR_5 GAME_TIME - 4628 * 6

#define DRAIN_RATE_NIGHT_1 588 // 9.8 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_2 360 // 6 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_3 300 // 5 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_4 240 // 4 seconds per 1% battery drain
#define DRAIN_RATE_NIGHT_5 180 // 3 seconds per 1% battery drain

// TODO: CHANGE
static const int DRAIN_RATE_PER_NIGHT[] = {
    DRAIN_RATE_NIGHT_1,
    DRAIN_RATE_NIGHT_2,
    DRAIN_RATE_NIGHT_3,
    DRAIN_RATE_NIGHT_4,
    DRAIN_RATE_NIGHT_5
};

// TODO: Adjust this levels
#define BATTERY_DRAIN_RATE_DOOR 3
#define BATTERY_DRAIN_RATE_LIGHT 1
#define BATTERY_DRAIN_RATE_CAMERA 2
#define GAME_TIME 31800 // 8m 55s in ticks

typedef enum {
    TIMER_TICK,
    MOUSE_LB_CLICK,
    MOUSE_MOVE,
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
    NUM_EVENTS
} EventType;

// Tagged Union - TODO: instead of scancodes and mouse_packets, have enums that represent the keys
typedef struct {
    EventType type;
    union { // TODO: simplify this structs if only one field is needed for each event type
        uint8_t scancode; // TODO: this scancode can have more than just 1 byte (use uint16_t? or there can be 3 bytes?)
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

typedef enum {
    NIGHT_WIN,
    NIGHT_LOSE,
    NIGHT_UNKOWN
} NightResult;

// Global game data that persists across states
typedef struct {
    int current_night; // 0 (no current night), 1 to 5 - also used to determine night's gimmicks

    // mouse coordinates for displaying it
    int mouse_x;
    int mouse_y;
    NightResult last_night_result; 
} PersistentData;
 
// Camera IDs
typedef enum { CAM_1A, CAM_1B, CAM_2A, CAM_2B } CameraID;

typedef enum {
    NEW_GAME,
    EXIT_GAME
} MainMenuOption;

typedef struct {
    MainMenuOption selected_option; // for keyboard navigation in main menu; 0 for no option selected
} MainMenuState;

typedef struct {
    int time_left; // equivalent to 8m 55s in ticks (assuming 60 ticks per second, 8m 55s would be 8*60*60 + 55*60 = 31800 ticks)

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

// Specific data for a sequence of changing images without player input
typedef struct {
    int frame_index; // Which frame of the jumpscare animation
    int tick_timer; // Counter to control animation speed
    AnimatronicName animatronic_name; // Which character is jumpscaring?
} JumpscareState;

// Tagged Union to represent the current game state
typedef struct {
    PersistentData global_data; // Global data across all states
    StateType type; // tag
    union {
        MainMenuState main_menu;
        NightSurvivalState night;
        JumpscareState jumpscare;
    } data; // state-specific data
} GameState;

JumpscareState init_jumpscare_state(AnimatronicName animatronic_name) {
    JumpscareState state;
    state.frame_index = 0;
    state.tick_timer = 0;
    state.animatronic_name = animatronic_name;
    return state;
}

#endif /* STATE_H */

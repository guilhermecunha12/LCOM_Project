#ifndef STATE_H
#define STATE_H

#include "../lab4/mouse.h"
#include "models/animatronic.h"
#include "game_constants.h"
#include "models/sprite.h"

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
    NEWSPAPER,
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
    LEFT,
    RIGHT,
    NO_MOVEMENT
} MovementDirection;

// Global game data that persists across states
typedef struct {
    int current_night; // 0 (no current night), 1 to 5 - also used to determine night's gimmicks

    // mouse coordinates for displaying it
    int mouse_x;
    int mouse_y;

    // Shared data for states that have camera movement (e.g., night survival and night no battery)
    int background_offset_x;
    MovementDirection moving; // -1 for moving left, 0 for not moving, 1 for moving right
} PersistentData;

typedef enum {
    NO_OPTION,
    NEW_GAME,
    CONTINUE,
    EXIT_GAME
} MainMenuOption;

typedef struct {
    int num_options; // number of options to display in the main menu
    MainMenuOption selected_option; // for keyboard navigation in main menu; 0 for no option selected
    MainMenuOption* options; // options to display in the main menu, determined by the current night (if current_night is 0, options are "New Game" and "Exit". If current_night is greater than 0, options are "New Game", "Continue", and "Exit")
} MainMenuState;

typedef struct {
    int duration;
} NewspaperState;

typedef struct {
    int duration;
} NightIntroState;

typedef struct {
    int time_left;

    int power_level; // 100 - 0
    int power_drain_rate; // number of units needed to decrement power by 1 unit
    int power_drain_speed; // number of units equivalent for each tick

    bool left_light_on;
    bool right_light_on;
    bool left_door_closed;
    bool right_door_closed;
    bool camera_monitor_up; // Is the player looking at cameras?
    bool camera_animation_playing;
    AnimSprite* camera_monitor; // The animated sprite for the camera monitor flipping up or down
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
    AnimSprite* jumpscare_sprite;
    AnimatronicName animatronic_name;
} JumpscareState;

typedef struct {
    int frame_index;
    int tick_timer;
    int duration;
} Night6AMScreen;

typedef struct {
    int duration;
    AnimSprite* static_sprite;
} StaticScreenState;

typedef struct {
    int duration; // Counter to control how long the win screen is displayed
} WinState;

typedef struct {
    int duration;
} GameOverState;

// Tagged Union to represent the current game state
typedef struct {
    PersistentData global_data; // Global data across all states
    StateType type; // tag
    union {
        MainMenuState main_menu;
        NewspaperState newspaper;
        NightIntroState night_intro;
        NightSurvivalState night_survival;
        JumpscareState jumpscare;
        Night6AMScreen night_6am;
        NightNoBatteryState night_no_battery;
        WinState win;
        StaticScreenState static_screen;
        GameOverState game_over;
    } data; // state-specific data
} GameState;


void init_main_menu(GameState* state);
void init_night_intro(GameState* state);
void init_newspaper(GameState* state);
void init_night_survival(GameState* state);
void init_night_6am(GameState* state);
void init_night_no_battery(GameState* state);
void init_jumpscare(GameState* state, AnimatronicName animatronic_name);
void init_static_screen(GameState* state);
void init_game_over(GameState* state);
void init_win_screen(GameState* state);

#endif /* STATE_H */

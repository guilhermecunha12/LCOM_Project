#ifndef STATE_H
#define STATE_H

#include "../lab4/mouse.h"

typedef enum {
    TIMER_TICK,
    MOUSE_CLICK,
    MOUSE_MOVE,
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
    NUM_EVENTS
} EventType;

// Tagged Union
typedef struct {
    EventType type;
    union { // TODO: simplify this structs if only one field is needed for each event type
        uint8_t scancode; // TODO: this scancode can have more than just 1 byte (use uint16_t? or there can be 3 bytes?)
        struct packet mouse_packet;
        int timer_ticks;
    } data;
} GameEvent;

// Game states
typedef enum {
    MAIN_MENU,
    NIGHT_INTRO,
    NIGHT_SURVIVAL,
    NIGHT_TRANSITION, // E.g., The "6 AM! Next Night" screen
    JUMPSCARE,
    NIGHT_END,
    EXIT,
    NUM_STATES
} StateType;

// Global game data that persists across states
typedef struct {
    int current_night; // 1 to 5

    // mouse coordinates for displaying it
    int mouse_x;
    int mouse_y;
} PersistentData;
 
// Camera IDs
typedef enum { CAM_1A, CAM_1B, CAM_2A, CAM_2B } CameraID;

typedef struct {
    int selected_option; // for keyboard navigation in main menu
} MainMenuState;

typedef struct {
    int time_ticks; // E.g., 0 to roughly 6*60*60 (6 hours in game)
    int power_level; // 10000 -> 100% (stored as int to allow slow drain?)
    bool left_door_closed;
    bool right_door_closed;
    bool camera_monitor_up; // Is the player looking at cameras?
    CameraID viewing_camera;
    
    // For timer-driven animations (e.g., fan spinning, camera static)
    int fan_frame_index;
    int static_animation_timer;
} NightSurvivalState;

// Specific data for a sequence of changing images without player input
typedef struct {
    int frame_index; // Which frame of the jumpscare animation
    int tick_timer; // Counter to control animation speed
    int animatronic_id; // Which character is jumpscaring?
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

#endif /* STATE_H */

#ifndef STATE_H
#define STATE_H

#include "../lab4/mouse.h"
#include "models/animatronic.h"
#include "game_constants.h"
#include "models/sprite.h"
#include "devices/serial_port/queue.h"

#include <stdbool.h>

/**
 * @brief Enum that defines the type of events that can occur in the game.
 */
typedef enum {
    TIMER_TICK,
    MOUSE_LB_CLICK,
    MOUSE_MOVE,
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
    SERIAL_PORT_DATA,
    NUM_EVENTS
} EventType;

/**
 * @brief Enum that defines the keys that can be pressed in the game.
 */
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

/**
 * @brief Struct that represents an event in the game. It uses a tagged union to store the relevant data for each type of event.
 */
typedef struct {
    EventType type;
    union {
        Key key;
        struct {int16_t delta_x; int16_t delta_y;} mouse_coords;
        int timer_ticks;
        Queue* serial_port_data;
    } data;
} GameEvent;

/**
 * @brief Enum that defines the different states of the game. Each state can have its own specific data, but they all share the same global data defined in the GameState struct.
 */
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

    // States for the receiver of the serial port data
    WAITING_FOR_DATA,
    RECEIVING_DATA,

    NUM_STATES
} StateType;

/**
 * @brief Enum that defines the direction of movement for states that have camera movement. This is used to determine the direction of the next camera movement after waiting.
 */
typedef enum {
    LEFT,
    RIGHT,
    NO_MOVEMENT
} MovementDirection;

// Global game data that persists across states
/**
 * @brief Enum that defines the global game data that persists across states. This includes the current night, mouse coordinates for displaying the cursor, and shared data for states that have camera movement.
 */
typedef struct {
    int current_night; // 0 (no current night), 1 to 5 - also used to determine night's gimmicks

    // mouse coordinates for displaying it
    int mouse_x;
    int mouse_y;

    // Shared data for states that have camera movement (e.g., night survival and night no battery)
    int background_offset_x;
    MovementDirection moving; // -1 for moving left, 0 for not moving, 1 for moving right
} PersistentData;

/**
 * @brief Enum that defines the options available in the main menu. This is used to determine which options to display in the main menu based on the current night.
 */
typedef enum {
    NO_OPTION,
    NEW_GAME,
    CONTINUE,
    EXIT_GAME
} MainMenuOption;

/* GAME STATES */
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
    bool left_door_animation_playing;
    bool right_door_animation_playing;
    bool camera_monitor_up; // Is the player looking at cameras?
    bool camera_animation_playing;
    AnimSprite* camera_monitor; // The animated sprite for the camera monitor flipping up or down
    AnimSprite* left_door; // The animated sprite for the left door opening or closing
    AnimSprite* right_door; // The animated sprite for the right door opening or closing
    CameraID viewing_camera;


    // For timer-driven animations (e.g., fan spinning, camera static)
    int fan_frame_index;
    int static_animation_timer;


    int wait_timer;
    int camera_offset_x;
    MovementDirection moving; // -1 for moving left, 0 for not moving, 1 for moving right
    MovementDirection last_camera_direction; // used to determine the direction of the next camera movement after waiting

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
    bool animatronics_in_cam[NUM_CAMERAS][NUM_ANIMATRONICS];
    CameraID animatronic_current_cam[NUM_ANIMATRONICS];
} ReceivingDataState;
typedef struct {
    int duration;
} GameOverState;

/**
 * @brief Struct that represents the overall game state. It contains a type field that indicates the current state of the game, a union that holds the specific data for each state, and a PersistentData struct that holds data that persists across all states.
 */
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
        
        // Receiver-specific state
        ReceivingDataState receiving_data;
    } data; // state-specific data
} GameState;

/**
 * @brief Function that initializes the game state to the main menu and sets up the global data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_main_menu(GameState* state);

/**
 * @brief Function that initializes the game state to the night intro state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_night_intro(GameState* state);

/**
 * @brief Function that initializes the game state to the newspaper state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_newspaper(GameState* state);

/**
 * @brief Function that initializes the game state to the night survival state and sets up the relevant data, including the animatronics' paths and AI levels based on the current night.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_night_survival(GameState* state);

/**
 * @brief Function that initializes the game state to the 6 AM screen state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_night_6am(GameState* state);

/**
 * @brief Function that initializes the game state to the night no battery state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_night_no_battery(GameState* state);

/**
 * @brief Function that initializes the game state to the jumpscare state and sets up the relevant data, including the jumpscare sprite based on the animatronic that is performing the jumpscare.
 * @param state Pointer to the GameState struct to initialize.
 * @param animatronic_name The name of the animatronic that is performing the jumpscare, used to determine which jumpscare sprite to display.
 */
void init_jumpscare(GameState* state, AnimatronicName animatronic_name);

/**
 * @brief Function that initializes the game state to the win screen state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_static_screen(GameState* state);

/**
 * @brief Function that initializes the game state to the game over state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_game_over(GameState* state);

/**
 * @brief Function that initializes the game state to the win screen state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_win_screen(GameState* state);

/**
 * @brief Function that initializes the game state to the receiving data state and sets up the relevant data.
 * @param state Pointer to the GameState struct to initialize.
 * @param data_queue The queue containing the data received from the serial port. This is necessary because animatronic's position data is sent in the begginning of the night survival mode (in the same interrupt as the data that starts the night), so we need to process that data to initialize the animatronics' positions in the receiving data state.
 */
void init_receiving_data_state(GameState* state, Queue* data_queue);

#endif /* STATE_H */

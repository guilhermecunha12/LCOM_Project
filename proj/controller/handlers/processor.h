#ifndef HANDLERS_H
#define HANDLERS_H

#include "../../state.h"

/**
 * @brief Type alias for event handler functions (return void and take pointers to GameState and GameEvent)
 */
typedef void (*EventHandler)(GameState*, const GameEvent*);

/**
 * @brief Get the appropriate event handler for the given GameState and EventType
 * @details Internally, the implementation uses a 2D array indexed with GameState and EventType to retrieve the correct handler function. If no handler is defined for the given state and event type, it returns NULL.
 * @param state The current state of the game, used to determine which set of event handlers to use.
 * @param event The current event type, used to determine which specific handler to call.
 * @return The appropriate function pointer to a event handler function. 
 */
EventHandler get_event_handler(const StateType state, const EventType event);

                /* Mouse  Related Handlers */

/**
 * @brief Handler for mouse movement events, which updates the mouse coordinates in the global game state. It is used in MAIN_MENU and NIGHT_SURVIVAL states.
 * @param state Pointer to the current game state, which will be modified with the new mouse coordinates.
 * @param event Pointer to the current game event, which contains the mouse movement data (delta_x and delta_y).
 */
void general_mouse_move(GameState* state, const GameEvent* event);

/**
 * @brief Calls general_mouse_move and then checks if the mouse is inside any of the main menu options (New Game, Continue, Exit Game) to update the selected option in the main menu state accordingly.
 * @param state Pointer to the current game state, which will be modified based on the mouse coordinates.
 * @param event Pointer to the current game event, which contains the mouse movement data (delta_x and delta_y).
 */
void handle_main_menu_mouse_move(GameState* state, const GameEvent* event);


/**
 * @brief Handler for mouse left button click events in the main menu state. It checks if the click was on the "New Game" "Continue" or "Exit Game" buttons and updates the game state accordingly (starting a new game or exiting).
 * @param state Pointer to the current game state, which will be modified based on the click.
 * @param event Pointer to the current game event, which contains the mouse click data. 
 */
void handle_main_menu_mouse_click(GameState* state, const GameEvent* event);

/**
 * @brief Handler for mouse left button click events in the night survival state. It checks if the click was on any interactive elements and updates the game state accordingly.
 * @param state Pointer to the current game state, which will be modified based on the click.
 * @param event Pointer to the current game event, which contains the mouse click data.
 */
void handle_night_survival_mouse_click(GameState* state, const GameEvent* event);

                /* Timer Related Handlers */

/**
 * @brief Handler for timer tick events in the newspaper state.
 * @param state Pointer to the current game state, which will be modified based on the timer event.
 * @param event Pointer to the current game event.
 */
void handle_newspaper_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the night intro state. This handler decrements the duration of the night intro screen and transitions to the night survival state when the duration reaches zero. It also initializes the night survival state with the current night number from the global game state.
 * @param state Pointer to the current game state, which will be modified to transition to the night survival state when the night intro duration ends.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_night_intro_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the night survival state. This handler manages the countdown of the night survival time, checks for night completion, and handles battery drain based on player actions (doors, lights, camera). It transitions to the night 6AM screen if the player survives the night or to the no battery screen if the battery level reaches zero. It also updates animations and checks for animatronic jumpscares.
 * @param state Pointer to the current game state, which will be modified based on the night survival timer events, including time left, battery level, and potential jumpscares.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_night_survival_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the win screen state. This handler manages the countdown for the win screen display and transitions to the main menu state when the duration reaches zero, initializing the main menu state in the process.
 * @param state Pointer to the current game state, which will be modified to transition to the next state when the win screen duration ends.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_win_screen_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the static screen state. This handler manages the countdown for the static screen display and transitions to the game over state when the duration reaches zero, initializing the game over state in the process.
 * @param state Pointer to the current game state, which will be modified to transition to the game over state when the static screen duration ends.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_static_screen_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the night 6AM state. This handler manages the countdown for the night 6AM screen display and transitions and initializes the night intro state when the duration reaches zero or if it was the last night it will transition to the win state.
 * @param state Pointer to the current game state, which will be modified to transition to the next state when the night 6AM duration ends.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_night_6am_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the night no battery state. This handler manages the countdown for the night no battery screen display and transitions to the night 6AM state when the duration reaches zero, initializing the night 6AM state in the process.
 * @param state Pointer to the current game state, which will be modified to transition to the night 6AM state when the night no battery duration ends.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_night_no_battery_timer(GameState* state, const GameEvent* event);

/**
 * @brief Handler for timer tick events in the jumpscare state. This handler manages the countdown for the jumpscare screen display and transitions to the static screen state when the duration reaches zero, initializing the static screen state in the process.
 * @param state Pointer to the current game state, which will be modified to transition to the static screen state when the jumpscare duration ends.
 * @param event Pointer to the current game event, which contains the timer tick data.
 */
void handle_jumpscare_timer(GameState* state, const GameEvent* event);


                /* Keyboard Related Handlers */

/**
 * @brief Handler for keyboard events in the main menu state. This handler manages keyboard input for navigating the main menu options (e.g., moving selection up/down and executing the selected option).
 * @param state Pointer to the current game state, which will be modified to update the main menu selection.
 * @param event Pointer to the current game event, which contains the keyboard input data.
 */
void handle_main_menu_keyboard(GameState* state, const GameEvent* event);


/**
 * @brief Handler for keyboard events in the night survival state. This handler manages keyboard input for controlling the player's actions during the night survival state (e.g., moving the camera view left or right) or consulting the camera menu by pressing space.
 * @param state Pointer to the current game state, which will be modified based on the player's keyboard input during the night survival state.
 * @param event Pointer to the current game event, which contains the keyboard input data.
 */
void handle_night_survival_keyboard(GameState* state, const GameEvent* event);

/**
 * @brief Handler for keyboard events in the night no battery state. This handler manages keyboard input such as moving the camera view left or right
 * @param state Pointer to the current game state, which will be modified based on the player's keyboard input during the night no battery state.
 * @param event Pointer to the current game event, which contains the keyboard input data.
 */
void handle_night_no_battery_keyboard(GameState* state, const GameEvent* event);

// TODO: REMOVE! ONLY FOR FASTER TESTING
void go_to_night_survive(GameState* state, const GameEvent* event);

#endif /* HANDLERS_H */



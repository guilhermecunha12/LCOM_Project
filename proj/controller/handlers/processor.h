#ifndef HANDLERS_H
#define HANDLERS_H

#include "../../state.h"

// Type alias for event handler functions (return void and take pointers to GameState and GameEvent)
typedef void (*EventHandler)(GameState*, const GameEvent*);

// Function to get the appropriate event handler based on the current state and event type
EventHandler get_event_handler(StateType state, EventType event);

// Handlers
void handle_main_menu_keyboard(GameState* state, const GameEvent* event);

/**
 * @brief Handler for mouse movement events, which updates the mouse coordinates in the global game state. It is used in MAIN_MENU and NIGHT_SURVIVAL states.
 * @param state Pointer to the current game state, which will be modified with the new mouse coordinates.
 * @param event Pointer to the current game event, which contains the mouse movement data (delta_x and delta_y).
 */
void handle_mouse_move(GameState* state, const GameEvent* event);

/**
 * @brief Handler for mouse left button click events in the main menu state. It checks if the click was on the "New Game" or "Exit Game" buttons and updates the game state accordingly (starting a new game or exiting).
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

// Timer Related Handlers 

void handle_night_intro_timer(GameState* state, const GameEvent* event);

void handle_night_survival_timer(GameState* state, const GameEvent* event);

void handle_win_screen_timer(GameState* state, const GameEvent* event);

void handle_static_screen_timer(GameState* state, const GameEvent* event);

void handle_night_6am_timer(GameState* state, const GameEvent* event);

void handle_night_no_battery_timer(GameState* state, const GameEvent* event);

void handle_jumpscare_timer(GameState* state, const GameEvent* event);

#endif /* HANDLERS_H */



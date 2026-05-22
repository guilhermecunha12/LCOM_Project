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
 * @brief Handler for mouse movement events, which updates the mouse coordinates in the global game state. It is used accross several states except in the jumpscare state, where the mouse is hidden
 * @param state Pointer to the current game state, which will be modified with the new mouse coordinates.
 * @param event Pointer to the current game event, which contains the mouse movement data (delta_x and delta_y).
 */
void handle_mouse_move(GameState* state, const GameEvent* event);
void handle_main_menu_mouse_click(GameState* state, const GameEvent* event);
void handle_night_survival_mouse_click(GameState* state, const GameEvent* event);
/* Night survival handlers, other state handlers... */

#endif /* HANDLERS_H */



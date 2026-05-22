#ifndef HANDLERS_H
#define HANDLERS_H

#include "../../state.h"

// Type alias for event handler functions (return void and take pointers to GameState and GameEvent)
typedef void (*EventHandler)(GameState*, const GameEvent*);

// Function to get the appropriate event handler based on the current state and event type
EventHandler get_event_handler(StateType state, EventType event);

// Handlers
void handle_main_menu_keyboard(GameState* state, const GameEvent* event);
void handle_main_menu_mouse(GameState* state, const GameEvent* event);
void handle_night_intro_timer(GameState* state, const GameEvent* event);

#endif /* HANDLERS_H */



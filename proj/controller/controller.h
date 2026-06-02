#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../state.h"

/**
 * @brief Processes a game event, calling the appropriate event handler and updates the game state accordingly
 * @param state Pointer to the current game state, which will be modified based on the event. 
 * @param event Pointer to the game event to be processed.
 */
void process_event(GameState* state, const GameEvent* event);

#endif /* CONTROLLER_H */

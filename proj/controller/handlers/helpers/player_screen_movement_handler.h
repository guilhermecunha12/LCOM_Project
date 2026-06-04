#ifndef PLAYER_SCREEN_MOVEMENT_HANDLER_H
#define PLAYER_SCREEN_MOVEMENT_HANDLER_H

#include "../../../state.h"
#include "../../../view/ui.h"

/**
 * @brief Helper function to move the player's screen to the left.
 * @details This function was created since code would be duplicated in both night survival and night no battery handlers, and it is better to have it in a single place. It modifies the background movement direction to LEFT.
 * @param state Pointer to the current game state, which will be modified to update the background movement direction.
 */
void move_player_screen_left(GameState* state);

/**
 * @brief Helper function to move the player's screen to the right.
 * @details This function was created since code would be duplicated in both night survival and night no battery handlers, and it is better to have it in a single place. It modifies the background movement direction to RIGHT.
 * @param state Pointer to the current game state, which will be modified to update the background movement direction.
 */
void move_player_screen_right(GameState* state);

#endif /* PLAYER_SCREEN_MOVEMENT_HANDLER_H */

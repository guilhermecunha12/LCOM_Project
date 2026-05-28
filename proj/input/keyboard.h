#include "../../lab3/kbc.h"
#include "../state.h"
#include <stdint.h>

/**
 * @brief Updates the GameEvent struct based on the scancode received from the keyboard interrupt.
 * @details This function processes the scancode received from the keyboard interrupt, determines if it's a key press or release, and updates the GameEvent struct accordingly. It also normalizes the scancode to get the mapped key and updates the event data if the key is relevant for the game.
 * @param ge A pointer to the GameEvent struct to be updated with the keyboard event information.
 * @return int Returns 0 if the GameEvent was successfully updated with a keyboard event, or -1 if there was an error processing the scancode (e.g., no scancode available).
 */
int update_game_event(GameEvent* ge);

#ifndef EVENT_UPDATER_H
#define EVENT_UPDATER_H

#include "../state.h"
#include "../../lab2/timer_count.h"
#include "../../lab3/kbc.h"
#include "../../lab4/mouse.h"
#include "serial_port/serial_port.h"

/**
 * @brief Updates the GameEvent struct with timer tick information.
 * @param ge A pointer to the GameEvent struct to be updated with the timer tick event information.
 * @return int Returns 0 on success, which always happens.
 */
int update_timer_game_event(GameEvent* ge);

/**
 * @brief Updates the GameEvent struct based on the scancode received from the keyboard interrupt.
 * @details This function processes the scancode received from the keyboard interrupt, determines if it's a key press or release, and updates the GameEvent struct accordingly. It also normalizes the scancode to get the mapped key and updates the event data if the key is relevant for the game.
 * @param ge A pointer to the GameEvent struct to be updated with the keyboard event information.
 * @return int Returns 0 if the GameEvent was successfully updated with a keyboard event, or 1 if there was an error processing the scancode (e.g., no scancode available).
 */
int update_keyboard_game_event(GameEvent* ge);

int update_mouse_game_event(GameEvent* ge);

int update_serial_port_game_event(GameEvent* ge);

#endif /* EVENT_UPDATER_H */

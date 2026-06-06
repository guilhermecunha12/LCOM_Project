#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <stdbool.h>
#include "../models/sprite.h"
#include "../state.h"

/**
 * @brief Utility function to check if the mouse cursor is inside a given rectangular box. This is used for checking if the mouse is hovering over or clicking on interactive elements in the UI.
 * @param mouse_x The current x coordinate of the mouse cursor.
 * @param mouse_y The current y coordinate of the mouse cursor.
 * @param box_x The x coordinate of the top-left corner of the rectangular box.
 * @param box_y The y coordinate of the top-left corner of the rectangular box.
 * @param box_w The width of the rectangular box.
 * @param box_h The height of the rectangular box.
 * @return Returns true if the mouse cursor is inside the rectangular box and false otherwise.
 */
bool is_mouse_inside(int mouse_x, int mouse_y, int box_x, int box_y, int box_w, int box_h);

/**
 * @brief Utility function to draw the left door of the office in the night survival mode, based on the current state of the door (open or closed), the light (on or off) and if there is an animatronic at the door or not. This function also takes care of drawing the door animation on top of everything else if it is currently playing.
 * @param state The current game state, which contains all the necessary information to determine how to draw the left door.
 */
void draw_left_door(const GameState *state);

/**
 * @brief Utility function to draw the right door of the office in the night survival mode, based on the current state of the door (open or closed), the light (on or off) and if there is an animatronic at the door or not. This function also takes care of drawing the door animation on top of everything else if it is currently playing.
 * @param state The current game state, which contains all the necessary information to determine how to draw the right door.
 */
void draw_right_door(const GameState *state);

/**
 * @brief Utility function to draw the left door button in the night survival mode, based on whether the left door is currently closed or open. The button will be drawn in green if the door is closed and in red if the door is open.
 * @param state The current game state, which contains the necessary information to determine the state of the left door and how to draw the button accordingly.
 */
void draw_left_door_button(const GameState *state);

/**
 * @brief Utility function to draw the right door button in the night survival mode, based on whether the right door is currently closed or open. The button will be drawn in green if the door is closed and in red if the door is open.
 * @param state The current game state, which contains the necessary information to determine the state of the right door and how to draw the button accordingly.
 */
void draw_right_door_button(const GameState *state);

/**
 * @brief Utility function to draw the left light button in the night survival mode, based on whether the left light is currently on or off. The button will be drawn in green if the light is on and in red if the light is off.
 * @param state The current game state, which contains the necessary information to determine the state of the left light and how to draw the button accordingly.
 */
void draw_left_light_button(const GameState *state);

/**
 * @brief Utility function to draw the right light button in the night survival mode, based on whether the right light is currently on or off. The button will be drawn in green if the light is on and in red if the light is off.
 * @param state The current game state, which contains the necessary information to determine the state of the right light and how to draw the button accordingly.
 */
void draw_right_light_button(const GameState *state);

#endif /* UI_UTILS_H */

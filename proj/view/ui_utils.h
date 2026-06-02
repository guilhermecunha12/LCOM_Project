#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <stdbool.h>

/**
 * @brief Utility function to check if the mouse cursor is inside a given rectangular box. This is used for checking if the mouse is hovering over or clicking on interactive elements in the UI.
 * @param mouse_x The current x coordinate of the mouse cursor.
 * @param mouse_y The current y coordinate of the mouse cursor.
 * @param box_x The x coordinate of the top-left cornex of the rectangular box.
 * @param box_y The y coordinate of the top-left cornex of the rectangular box.
 * @param box_w The width of the rectangular box.
 * @param box_h The height of the rectangular box.
 * @return Returns true if the mouse cursor is inside the rectangular box and false otherwise.
 */
bool is_mouse_inside(int mouse_x, int mouse_y, int box_x, int box_y, int box_w, int box_h);

#endif /* UI_UTILS_H */

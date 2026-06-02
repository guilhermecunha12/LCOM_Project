#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <stdbool.h>

// helper function to check if mouse is inside a box in an image
bool is_mouse_inside(int mouse_x, int mouse_y, int box_x, int box_y, int box_w, int box_h);

#endif /* UI_UTILS_H */

#include "ui_utils.h"

bool is_mouse_inside(int mouse_x, int mouse_y, int box_x, int box_y, int
box_w, int box_h) {
    return (
        mouse_x >= box_x && mouse_x <= box_x + box_w &&
        mouse_y >= box_y && mouse_y <= box_y + box_h
    );
}

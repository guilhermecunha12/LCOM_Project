#ifndef RENDERER_H
#define RENDERER_H

#include "../../state.h"

// Type alias for render handler functions
typedef void (*RenderHandler)(const GameState*);

RenderHandler get_render_handler(StateType state);
void draw_mouse(int x, int y); // TODO: implement: draws the mouse cursor at the given coordinates

// Render handlers for each state
void render_main_menu(const GameState* state);


#endif /* RENDERER_H */
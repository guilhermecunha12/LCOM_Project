#ifndef RENDERER_H
#define RENDERER_H

#include "../../state.h"

// Type alias for render handler functions
typedef void (*RenderHandler)(const GameState*);

RenderHandler get_render_handler(StateType state);
void draw_mouse(const GameState* state);

// Render handlers for each state
void render_main_menu(const GameState* state);
void render_night_intro(const GameState* state);

void render_night_survival(const GameState *state);

#endif /* RENDERER_H */

#ifndef VIEW_H
#define VIEW_H

#include "../state.h"

void draw_mouse(const GameState* state);

// This function draws the current frame in the back buffer; it does not modify the current game state
void render_frame(const GameState* state);

#endif /* VIEW_H */

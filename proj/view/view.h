#ifndef VIEW_H
#define VIEW_H

#include "../state.h"
/**
 * @brief This function is responsible for drawing the mouse cursor on top of everythin else.
 * @details The mouse is only drawn in states where it should be visible (MAIN_MENU and NIGHT_SURVIVAL). It uses the mouse coordinates stored in the global data of the game state to position the cursor sprite correctly on the screen.
 */
void draw_mouse(const GameState* state);

// This function draws the current frame in the back buffer; it does not modify the current game state
/**
 * @brief Function to render the current frame based on the game state.
 * @details This function first checks if the state type is valid. It then clears the back buffer and retrieves the appropriate render handler for the current state type. If a handler exists, it calls the handler to render the specific elements of that state. After rendering the state-specific elements, it calls `draw_mouse` to ensure the mouse cursor is drawn on top of everything else. Finally, it swaps the buffers to display the rendered frame on the screen.
 * @param state A pointer to the current game state, which contains all the necessary information to determine what to render on the screen.
 */
void render_frame(const GameState* state);

#endif /* VIEW_H */

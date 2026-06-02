#include "handlers/renderer.h"
#include "../models/assets.h"
#include "../models/sprite.h"
#include "../../lab5/video.h"

/*
void draw_mouse(const GameState* state) {
    // only draw the mouse in states where it should be visible
    if (state->type == MAIN_MENU || state->type == NIGHT_SURVIVAL) {
        // Draw the mouse on top of everything else
        Sprite* cursor = get_cursor_sprite();
        if (cursor) {
            draw_sprite(cursor, state->global_data.mouse_x, state->global_data.mouse_y); // TODO: implement this function inside video.c. The sprite holds its current position.
        }
    }
}
*/

void render_frame(const GameState* state) {
    if (state->type >= NUM_STATES) return;

    clear_back_buffer();
  
    RenderHandler handler = get_render_handler(state->type);

    if (handler) {
        handler(state); // Dispatch to the specific state's drawing code
    }

    //draw_mouse(state); // Draw the mouse on top of everything else
    swap_buffers();
}

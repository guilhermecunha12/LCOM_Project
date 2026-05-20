#include "handlers/renderer.h"
#include "../models/assets.h"
#include "../models/sprite.h"

void render_frame(const GameState* state) {
    if (state->type >= NUM_STATES) return;
  
    RenderHandler handler = get_render_handler(state->type);

    if (handler) {
        handler(state); // Dispatch to the specific state's drawing code
    }

    // Draw the mouse on top of everything else
    Sprite* cursor = get_cursor_sprite();
    if (cursor) {
        draw_sprite(cursor, state->global_data.mouse_x, state->global_data.mouse_y); // TODO: implementing this function inside video.c. The sprite holds its current position.
    }

    swap_buffers(); // TODO: implement double buffering inside video.c maybe
}
#include "handlers/renderer.h"
#include "../models/assets.h"
#include "../models/sprite.h"
#include "../devices/video/video.h"

// Draws the mouse on top of everything elses
void draw_mouse(const GameState* state) {
    // only draw the mouse in states where it should be visible
    if (state->type == MAIN_MENU || state->type == NIGHT_SURVIVAL) {
        
        Sprite* cursor = get_asset(CURSOR);
        cursor->x = state->global_data.mouse_x;
        cursor->y = state->global_data.mouse_y;
        draw_sprite(cursor);
    }
}

void render_frame(const GameState* state) {
    if (state->type >= NUM_STATES) return;

    RenderHandler handler = get_render_handler(state->type);
    if (handler) {
        handler(state);
    }

    draw_mouse(state); // Draw the mouse on top of everything else
    vg_flip_buffer();
}

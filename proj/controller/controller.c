#include <lcom/lcf.h>

#include "controller.h"
#include "../state.h"
#include "handlers/processor.h"

void process_event(GameState* state, GameEvent* event) {

    // TODO: review and maybe place this inside a function
    if (event->type == MOUSE_MOVE) {
        state->global_data.mouse_x += event->data.mouse_packet.delta_x;
        state->global_data.mouse_y -= event->data.mouse_packet.delta_y; 
        
        // Clamp to screen bounds
        if (state->global_data.mouse_x < 0) state->global_data.mouse_x = 0;
        if (state->global_data.mouse_y < 0) state->global_data.mouse_y = 0;
        if (state->global_data.mouse_x > SCREEN_WIDTH-1) state->global_data.mouse_x = SCREEN_WIDTH-1;
        if (state->global_data.mouse_y > SCREEN_HEIGHT-1) state->global_data.mouse_y = SCREEN_HEIGHT-1;
    }

    EventHandler handler = get_event_handler(state->type, event->type);

    if (handler) {
        handler(state, event);
    }
}
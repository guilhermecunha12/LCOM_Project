#include "processor.h"
#include "../../view/ui.h"

// 2D array of event handlers indexed by state and event type (eth - event handler table)
// Using Designated Initializers
static EventHandler eht[NUM_STATES][NUM_EVENTS] = {

    [MAIN_MENU] = {
        [KEYBOARD_PRESS] = handle_main_menu_keyboard,
        [MOUSE_LB_CLICK] = handle_main_menu_mouse_click,
        [MOUSE_MOVE] = handle_mouse_move,
        // Other main menu event handlers...
    },

    [NIGHT_SURVIVAL] = {
        [MOUSE_LB_CLICK] = handle_night_survival_mouse_click,
        [MOUSE_MOVE] = handle_mouse_move,
        // Night survival event handlers...
    },
    // Other states...
};

void handle_mouse_move(GameState* state, const GameEvent* event) {

    if (state->type == MAIN_MENU) {
        state->data.main_menu.selected_option = 0; // deselect main menu keyboard selection on mouse move
    }

    state->global_data.mouse_x += event->data.mouse_coords.delta_x;
    state->global_data.mouse_y -= event->data.mouse_coords.delta_y;

    // Clamp to screen bounds
    if (state->global_data.mouse_x < 0) state->global_data.mouse_x = 0;
    if (state->global_data.mouse_y < 0) state->global_data.mouse_y = 0;
    if (state->global_data.mouse_x > SCREEN_WIDTH-1) state->global_data.mouse_x = SCREEN_WIDTH-1;
    if (state->global_data.mouse_y > SCREEN_HEIGHT-1) state->global_data.mouse_y = SCREEN_HEIGHT-1;
}

EventHandler get_event_handler(StateType state, EventType event) {
    if (state >= NUM_STATES || event >= NUM_EVENTS) {
        return NULL; // Invalid state or event
    }
    return eht[state][event];
}


#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"

// 2D array of event handlers indexed by state and event type (eth - event handler table)
static EventHandler eht[NUM_STATES][NUM_EVENTS] = {

    [MAIN_MENU] = {
        // Guarantees that only presses are registered in the main menu
        [KEYBOARD_PRESS] = handle_main_menu_keyboard,
        [MOUSE_LB_CLICK] = handle_main_menu_mouse_click,
        [MOUSE_MOVE] = handle_main_menu_mouse_move,
    },

    [NEWSPAPER] = {
        [TIMER_TICK] = handle_newspaper_timer,
    },

    [NIGHT_INTRO] = {
        [TIMER_TICK] = handle_night_intro_timer,
    },

    [NIGHT_SURVIVAL] = {
        [KEYBOARD_PRESS] = handle_night_survival_keyboard,
        [MOUSE_LB_CLICK] = handle_night_survival_mouse_click,
        [MOUSE_MOVE] = general_mouse_move,
        [TIMER_TICK] = handle_night_survival_timer,
    },

    [NIGHT_NO_BATTERY] = {
        [KEYBOARD_PRESS] = handle_night_no_battery_keyboard,
        [TIMER_TICK] = handle_night_no_battery_timer,
    },

    [JUMPSCARE] = {
        [TIMER_TICK] = handle_jumpscare_timer,
    },
    
    [STATIC_SCREEN] = {
        [TIMER_TICK] = handle_static_screen_timer,
    },

    [WIN] = {
        [TIMER_TICK] = handle_win_screen_timer,
    },
    [NIGHT_6AM] = {
        [TIMER_TICK] = handle_night_6am_timer,
    },

    [GAME_OVER] = {
        [TIMER_TICK] = handle_game_over_timer,
    },


};

void general_mouse_move(GameState* state, const GameEvent* event) {

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

EventHandler get_event_handler(const StateType state, const EventType event) {
    if (state >= NUM_STATES || event >= NUM_EVENTS) {
        return NULL; // Invalid state or event
    }
    return eht[state][event];
}

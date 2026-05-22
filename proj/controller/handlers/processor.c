#include "processor.h"

// 2D array of event handlers indexed by state and event type (eth - event handler table)
// Using Designated Initializers
static EventHandler eht[NUM_STATES][NUM_EVENTS] = {

    [MAIN_MENU] = {
        [KEYBOARD_PRESS] = handle_main_menu_keyboard,
        [MOUSE_CLICK] = handle_main_menu_mouse,
        // Other main menu event handlers...
    },

    [NIGHT_INTRO] = {
        [TIMER_TICK] = handle_night_intro_timer,
    },

    [NIGHT_SURVIVAL] = {
        // Night survival event handlers...
    },
    // Other states...
};

EventHandler get_event_handler(StateType state, EventType event) {
    if (state >= NUM_STATES || event >= NUM_EVENTS) {
        return NULL; // Invalid state or event
    }
    return eht[state][event];
}


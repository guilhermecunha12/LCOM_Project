#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"

// Implementation of main menu event handlers

void handle_main_menu_mouse_click(GameState* state, GameEvent* event) {

    int mouse_x = state->global_data.mouse_x;
    int mouse_y = state->global_data.mouse_y;

    if (is_mouse_inside(mouse_x, mouse_y,
        MAIN_MENU_NEW_GAME_BUTTON_X,
        MAIN_MENU_NEW_GAME_BUTTON_Y,
        MAIN_MENU_NEW_GAME_BUTTON_W,
        MAIN_MENU_NEW_GAME_BUTTON_H)) {

        state->global_data.current_night = 1; // Start at night 1
        state->type = NIGHT_INTRO;
        
    } 

    // Leave a space reserved to this button even if not rendered. 
    else if (state->global_data.current_night > 0 && is_mouse_inside(mouse_x, mouse_y,
        MAIN_MENU_CONTINUE_BUTTON_X,
        MAIN_MENU_CONTINUE_BUTTON_Y,
        MAIN_MENU_CONTINUE_BUTTON_W,
        MAIN_MENU_CONTINUE_BUTTON_H)) {

        state->type = NIGHT_INTRO;
    }

    else if (is_mouse_inside(mouse_x, mouse_y,
        MAIN_MENU_EXIT_GAME_BUTTON_X,
        MAIN_MENU_EXIT_GAME_BUTTON_Y,
        MAIN_MENU_EXIT_GAME_BUTTON_W,
        MAIN_MENU_EXIT_GAME_BUTTON_H)) {

        state->type = EXIT;
    }
}
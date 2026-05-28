#include "processor.h"
#include "../../view/ui.h"
#include "../../view/ui_utils.h"

// Implementation of main menu event handlers

// Static helper functions

/**
 * @brief If no option is currently selected (i.e., selected_option == 0), select the first option (i.e., set selected_option to 1).
 * @param mm Pointer to the MainMenuState to modify
 */
static void menu_select_first_if_none(MainMenuState* mm) {
    if (mm->selected_option == 0) {
        mm->selected_option = 1;
    }
}

/**
 * @brief Move the selection up in the main menu. If no option is currently selected, select the first option. If the first option is currently selected, move the selection to the last option. Otherwise, move the selection up by one.
 * @param mm Pointer to the MainMenuState to modify
 */
static void menu_move_up(MainMenuState* mm) {
    menu_select_first_if_none(mm);
    if (mm->selected_option == 1) {
        mm->selected_option = mm->num_options;
    } else if (mm->selected_option > 1) {
        mm->selected_option--;
    }
}

/**
 * @brief Move the selection down in the main menu. If no option is currently selected, select the first option. If the last option is currently selected, move the selection to the first option. Otherwise, move the selection down by one.
 * @param mm Pointer to the MainMenuState to modify
 */
static void menu_move_down(MainMenuState* mm) {
    menu_select_first_if_none(mm);
    if (mm->selected_option == mm->num_options) {
        mm->selected_option = 1;
    } else if (mm->selected_option < mm->num_options) {
        mm->selected_option++;
    }
}

/**
 * @brief Execute the action associated with the currently selected option in the main menu. If no option is currently selected, do nothing.
 * @details If the current night is 0 (i.e., the player has not started a game yet), the options are "New Game" and "Exit". If the current night is greater than 0, the options are "New Game", "Continue", and "Exit". The "New Game" option starts a new game at night 1. The "Continue" option continues the current game at the current night. The "Exit" option exits the game.
 * @param state Pointer to the GameState to modify
 */
static void menu_execute_selected(GameState* state) {
    int sel = state->data.main_menu.selected_option;
    if (sel == NO_OPTION) return;

    if (state->global_data.current_night == 0) {
        switch (sel) {
            case NEW_GAME: // New Game
                state->global_data.current_night = 1;
                state->type = NIGHT_INTRO;
                state->data.night_intro = init_night_intro();
                break;
            case EXIT_GAME: // Exit
                state->type = EXIT;
                break;
            default:
                break;
        }
    } else {
        switch (sel) {
            case NEW_GAME: // New Game
                state->global_data.current_night = 1;
                state->type = NIGHT_INTRO;
                state->data.night_intro = init_night_intro();
                break;
            case CONTINUE: // Continue
                state->type = NIGHT_INTRO;
                state->data.night_intro = init_night_intro();
                break;
            case EXIT_GAME: // Exit
                state->type = EXIT;
                break;
            default:
                break;
        }
    }
}

void handle_main_menu_mouse_click(GameState* state, const GameEvent* event) {

    int mouse_x = state->global_data.mouse_x;
    int mouse_y = state->global_data.mouse_y;

    if (is_mouse_inside(mouse_x, mouse_y,
        NEW_GAME_X,
        NEW_GAME_Y,
        BOX_NEW_GAME_WIDTH,
        BOX_NEW_GAME_HEIGHT)) {

        state->global_data.current_night = 1; // Start at night 1
        state->type = NIGHT_INTRO;
        state->data.night_intro = init_night_intro();
    }

    // Leave a space reserved to this button even if not rendered. 
    else if (state->global_data.current_night > 0 && is_mouse_inside(mouse_x, mouse_y,
        CONTINUE_X,
        CONTINUE_Y,
        BOX_CONTINUE_WIDTH,
        BOX_CONTINUE_HEIGHT)) {

        state->type = NIGHT_INTRO;
        state->data.night_intro = init_night_intro();
    }
}

void handle_main_menu_keyboard(GameState* state, const GameEvent* event) {
    MainMenuState* mm = &state->data.main_menu;

    if (event->data.key == KEY_MENU_UP) {
        menu_move_up(mm);
    }
    else if (event->data.key == KEY_MENU_DOWN) {
        menu_move_down(mm);
    }
    else if (event->data.key == KEY_ENTER) {
        menu_execute_selected(state);
    }
}

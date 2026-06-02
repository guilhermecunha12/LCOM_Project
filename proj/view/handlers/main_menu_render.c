#include "../../models/sprite.h"
#include "../../models/assets.h"
#include "renderer.h"
#include "../ui.h"

#include <stdlib.h>

void render_main_menu(const GameState *state) {
    if (state == NULL)
    return;

    draw_sprite(get_asset(MENU_BG));
    draw_sprite(get_asset(GAME_TITLE));

    // Iterate over the options in the main menu and draw each one
    for (int i = 1; i <= state->data.main_menu.num_options; i++) {
        MainMenuOption option = state->data.main_menu.options[i];
        bool is_selected = (option == state->data.main_menu.selected_option);
        switch (option) {
            case NEW_GAME:
                draw_sprite(get_asset(is_selected ? OPT_NEWGAME_SEL : OPT_NEWGAME));
                break;
            case CONTINUE:
                draw_sprite(get_asset(is_selected ? OPT_CONTINUE_SEL : OPT_CONTINUE));
                break;
            case EXIT_GAME:
                draw_sprite(get_asset(is_selected ? OPT_EXIT_SEL : OPT_EXIT));
                break;
            default:
                break;
        }
    } 
}


    


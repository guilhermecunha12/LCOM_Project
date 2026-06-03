// models/assets.c
#include "assets.h"
#include "sprite.h"
#include "../view/ui.h"

#include "xpm/menu/menu.xpm"
#include "xpm/cursor.xpm"
#include "xpm/menu/title.xpm"
#include "xpm/menu/newgame.xpm"
#include "xpm/menu/newgame_sel.xpm"
#include "xpm/menu/continue.xpm"
#include "xpm/menu/continue_sel.xpm"
#include "xpm/menu/custom_night.xpm"
#include "xpm/menu/night1.xpm"
#include "xpm/menu/night2.xpm"
#include "xpm/menu/night3.xpm"
#include "xpm/menu/night4.xpm"
#include "xpm/menu/night5.xpm"
#include "xpm/menu/exit_game.xpm"
#include "xpm/menu/exit_game_sel.xpm"

static Sprite* assets[NUM_ASSETS] = {NULL};

void load_all_assets() {
    assets[MENU_BG] = create_sprite((xpm_map_t) menu_xpm, 0, 0);
    assets[CURSOR] = create_sprite((xpm_map_t) cursor_xpm, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    assets[GAME_TITLE] = create_sprite((xpm_map_t) title_xpm,GAME_TITLE_X, GAME_TITLE_Y);
    assets[OPT_NEWGAME] = create_sprite((xpm_map_t) newgame_xpm, NEW_GAME_X, NEW_GAME_Y);
    assets[OPT_NEWGAME_SEL] = create_sprite((xpm_map_t) newgame_sel_xpm,NEW_GAME_SEL_X, NEW_GAME_SEL_Y);
    assets[OPT_CONTINUE] = create_sprite((xpm_map_t) continue_xpm, CONTINUE_X, CONTINUE_Y);
    assets[OPT_CONTINUE_SEL] = create_sprite((xpm_map_t) continue_sel_xpm, CONTINUE_SEL_X, CONTINUE_SEL_Y);
    assets[OPT_EXIT] = create_sprite((xpm_map_t) exit_game_xpm, EXIT_GAME_X, EXIT_GAME_Y);
    assets[OPT_EXIT_SEL] = create_sprite((xpm_map_t) exit_game_sel_xpm, EXIT_GAME_SEL_X, EXIT_GAME_SEL_Y);
    assets[MENU_CUSTOM_NIGHT] = create_sprite((xpm_map_t) custom_night_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT1] = create_sprite((xpm_map_t) night1_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT2] = create_sprite((xpm_map_t) night2_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT3] = create_sprite((xpm_map_t) night3_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT4] = create_sprite((xpm_map_t) night4_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    assets[MENU_NIGHT5] = create_sprite((xpm_map_t) night5_xpm, NIGHT_TEXT_X, NIGHT_TEXT_Y);
    // TODO: include loops to load the jumpscare sprites
}

void unload_all_assets() {
    for (int i = 0; i < NUM_ASSETS; i++) {
        destroy_sprite(assets[i]);
        assets[i] = NULL;
    }
}

Sprite* get_asset(xpmASSET asset) {
    if (asset >= NUM_ASSETS) return NULL;
    return assets[asset];
}


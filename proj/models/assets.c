// models/assets.c
#include "assets.h"
#include "sprite.h"

#include "xpm/menu/menu.xpm"
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

static Sprite* assets[NUM_ASSETS] = {NULL};

void load_all_assets() {
    assets[MENU_BG] = create_sprite((xpm_map_t) menu_xpm);
    assets[GAME_TITLE] = create_sprite((xpm_map_t) title_xpm);
    assets[OPT_NEWGAME] = create_sprite((xpm_map_t) newgame_xpm);
    assets[OPT_NEWGAME_SEL] = create_sprite((xpm_map_t) newgame_sel_xpm);
    assets[OPT_CONTINUE] = create_sprite((xpm_map_t) continue_xpm);
    assets[OPT_CONTINUE_SEL] = create_sprite((xpm_map_t) continue_sel_xpm);
    assets[MENU_CUSTOM_NIGHT] = create_sprite((xpm_map_t) custom_night_xpm);
    assets[MENU_NIGHT1] = create_sprite((xpm_map_t) night1_xpm);
    assets[MENU_NIGHT2] = create_sprite((xpm_map_t) night2_xpm);
    assets[MENU_NIGHT3] = create_sprite((xpm_map_t) night3_xpm);
    assets[MENU_NIGHT4] = create_sprite((xpm_map_t) night4_xpm);
    assets[MENU_NIGHT5] = create_sprite((xpm_map_t) night5_xpm);
}

void unload_all_assets() {
    for (int i = 0; i < NUM_ASSETS; i++) {
        destroy_sprite(assets[i]);
        assets[i] = NULL;
    }
}

Sprite* get_asset(xpmASSET asset) {
    if (asset < 0 || asset >= NUM_ASSETS) return NULL;
    return assets[asset];
}



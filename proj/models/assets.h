// models/assets.h
#ifndef ASSETS_H
#define ASSETS_H

#include "sprite.h"

void load_all_assets(); // using xpm_load() maybe
void unload_all_assets();

// Getter functions (Read-only access for the View)
Sprite* get_cursor_sprite();
Sprite* get_main_menu_bg_sprite();
/*...*/

#endif
// models/assets.c
#include "assets.h"
#include "sprite.h"

// TODO: review how to access xpm files
#include "xpm/cursor.xpm" 
#include "xpm/bg.xpm"

static Sprite* cursor_sprite = NULL;
static Sprite* main_menu_bg_sprite = NULL;

// TODO: review how to access xpm files...
void load_all_assets() {
    cursor_sprite = create_sprite(cursor_xpm); // the argument would be the xpm files
    main_menu_bg_sprite = create_sprite(bg_xpm);
}

void unload_all_assets() {
    destroy_sprite(cursor_sprite);
    destroy_sprite(main_menu_bg_sprite);
}

// PUBLIC Getter functions
Sprite* get_cursor_sprite() {
    return cursor_sprite;
}

Sprite* get_main_menu_bg_sprite() {
    return main_menu_bg_sprite;
}
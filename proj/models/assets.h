// models/assets.h
#ifndef ASSETS_H
#define ASSETS_H

#include "sprite.h"

/**
 * @brief Enum that simplifies the code visually in the corresponding functions as we'll load them by an enum val that is easily retrievable through an array that points to a specific sprite asset.
 */ 
typedef enum {
    MENU_BG,
    CURSOR,
    GAME_TITLE,
    OPT_NEWGAME,
    OPT_NEWGAME_SEL,
    OPT_CONTINUE,
    OPT_CONTINUE_SEL,
    MENU_CUSTOM_NIGHT,
    MENU_NIGHT1,
    MENU_NIGHT2,
    MENU_NIGHT3,
    MENU_NIGHT4,
    MENU_NIGHT5,
    
    NUM_ASSETS
} xpmASSET;


/**
 * @brief Loads all the existing assets into memory by initializing them to an array of 
 * pointers to sprite objects.
 */
void load_all_assets();

/**
 * @brief Erases all existing assets from memory and evades memory leaks
 */
void unload_all_assets();

/**
 * @brief Getter for a sprite represented by a specific enum values
 */
Sprite* get_asset(xpmASSET asset);

#endif

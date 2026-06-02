// models/assets.h
#ifndef ASSETS_H
#define ASSETS_H

#include "sprite.h"
#include "animatronic.h"

/**
 * @brief Enum tha simplifies the code visually in the corresponding functions as we'll load them by an enum val that is easily etirable through an array that points to a specific sprite asset.
 */

 
typedef enum {
    MENU_BG,
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

    /* CAMS */
    CAM_1A_EMPTY,
    CAM_1A_FREDDY,
    CAM_1A_BONNIE,
    CAM_1A_CHICA,
    CAM_1A_BONNIE_CHICA,
    CAM_1A_FREDDY_BONNIE,
    CAM_1A_FREDDY_BONNIE_CHICA,
    CAM_1B_EMPTY,
    CAM_1B_FREDDY,
    CAM_1B_BONNIE,
    CAM_1B_CHICA,
    CAM_1B_BONNIE_CHICA,
    CAM_1B_FREDDY_BONNIE,
    CAM_1B_FREDDY_BONNIE_CHICA,
    CAM_1C_EMPTY,
    CAM_1C_FOXY,
    CAM_2A_EMPTY,
    CAM_2A_BONNIE,
    CAM_2A_FOXY,
    CAM_2A_BONNIE_FOXY,
    CAM_2B_EMPTY,
    CAM_2B_FREDDY,
    CAM_2B_CHICA,
    CAM_2B_FREDDY_CHICA,
    CAM_3_EMPTY,
    CAM_3_BONNIE,
    CAM_4A_EMPTY,
    CAM_4A_CHICA,
    CAM_4B_EMPTY,
    CAM_4B_FREDDY,
    CAM_4B_CHICA,
    CAM_4B_FREDDY_CHICA,
    CAM_5_EMPTY,
    CAM_5_BONNIE,
    CAM_6_EMPTY,
    CAM_6_FREDDY,
    CAM_6_CHICA,
    CAM_6_FREDDY_CHICA,
    CAM_7_EMPTY,
    CAM_7_FREDDY,
    CAM_7_CHICA,
    CAM_7_FREDDY_CHICA,

    /* OFFICE */
    OFFICE,
    LEFT_DOOR_CLOSED,
    RIGHT_DOOR_CLOSED,
    BONNIE_LEFT_DOOR,
    FOXY_LEFT_DOOR,
    FREDDY_RIGHT_DOOR,
    CHICA_RIGHT_DOOR,


    NUM_ASSETS
} xpmASSET;

#define CAM_EMPTY  0
#define CAM_FREDDY (1 << FREDDY)
#define CAM_BONNIE (1 << BONNIE)
#define CAM_CHICA  (1 << CHICA)
#define CAM_FOXY   (1 << FOXY)

static const xpmASSET cam1a_assets[] = {
    [CAM_EMPTY] = CAM_1A_EMPTY,
    [CAM_FREDDY] = CAM_1A_FREDDY,
    [CAM_BONNIE] = CAM_1A_BONNIE,
    [CAM_CHICA] = CAM_1A_CHICA,
    [CAM_BONNIE | CAM_CHICA] = CAM_1A_BONNIE_CHICA,
    [CAM_FREDDY | CAM_BONNIE] = CAM_1A_FREDDY_BONNIE,
    [CAM_FREDDY | CAM_BONNIE | CAM_CHICA] = CAM_1A_FREDDY_BONNIE_CHICA,
};

static const xpmASSET cam1b_assets[] = {
    [CAM_EMPTY] = CAM_1B_EMPTY,
    [CAM_FREDDY] = CAM_1B_FREDDY,
    [CAM_BONNIE] = CAM_1B_BONNIE,
    [CAM_CHICA] = CAM_1B_CHICA,
    [CAM_BONNIE | CAM_CHICA] = CAM_1B_BONNIE_CHICA,
    [CAM_FREDDY | CAM_BONNIE] = CAM_1B_FREDDY_BONNIE,
    [CAM_FREDDY | CAM_BONNIE | CAM_CHICA] = CAM_1B_FREDDY_BONNIE_CHICA,
};

static const xpmASSET cam1c_assets[] = {
    [CAM_EMPTY] = CAM_1C_EMPTY,
    [CAM_FOXY] = CAM_1C_FOXY,
};

static const xpmASSET cam2a_assets[] = {
    [CAM_EMPTY] = CAM_2A_EMPTY,
    [CAM_BONNIE] = CAM_2A_BONNIE,
    [CAM_FOXY] = CAM_2A_FOXY,
    [CAM_BONNIE | CAM_FOXY] = CAM_2A_BONNIE_FOXY,
};

static const xpmASSET cam2b_assets[] = {
    [CAM_EMPTY] = CAM_2B_EMPTY,
    [CAM_FREDDY] = CAM_2B_FREDDY,
    [CAM_CHICA] = CAM_2B_CHICA,
    [CAM_FREDDY | CAM_CHICA] = CAM_2B_FREDDY_CHICA,
};

static const xpmASSET cam3_assets[] = {
    [CAM_EMPTY] = CAM_3_EMPTY,
    [CAM_BONNIE] = CAM_3_BONNIE,
};

static const xpmASSET cam4a_assets[] = {
    [CAM_EMPTY] = CAM_4A_EMPTY,
    [CAM_CHICA] = CAM_4A_CHICA,
};

static const xpmASSET cam4b_assets[] = {
    [CAM_EMPTY] = CAM_4B_EMPTY,
    [CAM_FREDDY] = CAM_4B_FREDDY,
    [CAM_CHICA] = CAM_4B_CHICA,
    [CAM_FREDDY | CAM_CHICA] = CAM_4B_FREDDY_CHICA,
};

static const xpmASSET cam5_assets[] = {
    [CAM_EMPTY] = CAM_5_EMPTY,
    [CAM_BONNIE] = CAM_5_BONNIE,
};

static const xpmASSET cam6_assets[] = {
    [CAM_EMPTY] = CAM_6_EMPTY,
    [CAM_FREDDY] = CAM_6_FREDDY,
    [CAM_CHICA] = CAM_6_CHICA,
    [CAM_FREDDY | CAM_CHICA] = CAM_6_FREDDY_CHICA,
};

static const xpmASSET cam7_assets[] = {
    [CAM_EMPTY] = CAM_7_EMPTY,
    [CAM_FREDDY] = CAM_7_FREDDY,
    [CAM_CHICA] = CAM_7_CHICA,
    [CAM_FREDDY | CAM_CHICA] = CAM_7_FREDDY_CHICA,
};

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

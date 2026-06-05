// models/assets.h
#ifndef ASSETS_H
#define ASSETS_H

#include "sprite.h"
#include "animatronic.h"

/**
 * @brief Enum that simplifies the code visually in the corresponding functions as we'll load them by an enum val that is easily retrievable through an array that points to a specific sprite asset.
 */ 
typedef enum {
    /* CURSOR */
    CURSOR,

    /* MAIN MENU */
    MENU_BG,
    GAME_TITLE,
    OPT_NEWGAME,
    OPT_NEWGAME_SEL,
    OPT_CONTINUE,
    OPT_CONTINUE_SEL,
    OPT_EXIT,
    OPT_EXIT_SEL,
    MENU_CUSTOM_NIGHT,
    MENU_NIGHT1,
    MENU_NIGHT2,
    MENU_NIGHT3,
    MENU_NIGHT4,
    MENU_NIGHT5,

    /* NIGHT 6AM */
    NIGHT_6AM_SCREEN,

    /* GAME OVER */
    GAME_OVER_SCREEN,

    /* NEWSPAPER */
    NEWSPAPER_FEUP,

    /* NIGHT INTRO */
    START_NIGHT1,
    START_NIGHT2,
    START_NIGHT3,
    START_NIGHT4,
    START_NIGHT5,

    /* CAMS MAP LAYOUT */
    CAMS_MAP,

    /* CAM UI BUTTONS */
    CAM_BUTTON_ACTIVE,
    CAM_BUTTON_INACTIVE,

    /* CAM LABEL TEXTS (drawn on top of each button) */
    CAM_TEXT_1A,
    CAM_TEXT_1B,
    CAM_TEXT_1C,
    CAM_TEXT_2A,
    CAM_TEXT_2B,
    CAM_TEXT_3,
    CAM_TEXT_4A,
    CAM_TEXT_4B,
    CAM_TEXT_5,
    CAM_TEXT_6,
    CAM_TEXT_7,

    /* SELECTED CAMERA ROOM NAME TEXTS (drawn at SELECTED_CAM_TEXT_X/Y) */
    SEL_TEXT_1A,
    SEL_TEXT_1B,
    SEL_TEXT_1C,
    SEL_TEXT_2A,
    SEL_TEXT_2B,
    SEL_TEXT_3,
    SEL_TEXT_4A,
    SEL_TEXT_4B,
    SEL_TEXT_5,
    SEL_TEXT_6,
    SEL_TEXT_7,

    /* CAMS */
    CAM_1A_EMPTY,
    CAM_1A_FREDDY,
    CAM_1A_BONNIE,
    CAM_1A_CHICA,
    CAM_1A_BONNIE_CHICA,
    CAM_1A_FREDDY_BONNIE,
    CAM_1A_FREDDY_BONNIE_CHICA,
    CAM_1A_FREDDY_CHICA,
    CAM_1B_EMPTY,
    CAM_1B_FREDDY,
    CAM_1B_BONNIE,
    CAM_1B_CHICA,
    CAM_1B_BONNIE_CHICA,
    CAM_1B_FREDDY_BONNIE,
    CAM_1B_FREDDY_CHICA,
    CAM_1B_FREDDY_BONNIE_CHICA,

    CAM_1C_EMPTY,
    CAM_1C_FOXY_1,
    CAM_1C_FOXY_2,
    CAM_1C_FOXY_3,
    
    CAM_2A_EMPTY,
    CAM_2A_BONNIE,
    CAM_2A_FOXY,
    CAM_2A_BONNIE_FOXY,
    CAM_2B_EMPTY,
    CAM_2B_BONNIE,
    CAM_2B_FOXY,
    CAM_2B_BONNIE_FOXY,
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

    /* BATTERY NUMBERS */
    I_POWER0,
    I_POWER1,
    I_POWER2,
    I_POWER3,
    I_POWER4,
    I_POWER5,
    I_POWER6,
    I_POWER7,
    I_POWER8,
    I_POWER9,

    II_POWER0,
    II_POWER1,
    II_POWER2,
    II_POWER3,
    II_POWER4,
    II_POWER5,
    II_POWER6,
    II_POWER7,
    II_POWER8,
    II_POWER9,

    PERCENTAGE_SIGN,
    POWER_USAGE,
    POWER_LEFT,
    USAGE1,
    USAGE2,
    USAGE3,
    USAGE4,

    CAMERA_FLIP_BUTTON,
    HOUR_12AM,
    HOUR_1AM,
    HOUR_2AM,
    HOUR_3AM,
    HOUR_4AM,
    HOUR_5AM,
    AM_TEXT,
    NIGHT_TEXT_1,
    NIGHT_TEXT_2,
    NIGHT_TEXT_3,
    NIGHT_TEXT_4,
    NIGHT_TEXT_5,

    /* OFFICE */
    // assests contiguos em memory for easier access in jumpscare animation frames
    /* JUMPSCARES — base index per animatronic, use FIRST + frame_index to address */
    JUMPSCARE_FREDDY_FIRST,  // 21 frames
    JUMPSCARE_FREDDY_LIGHTOUT_FIRST = JUMPSCARE_FREDDY_FIRST + NUM_JUMPSCARE_FREDDY_NORMAL, // 28 frames
    JUMPSCARE_BONNIE_FIRST = JUMPSCARE_FREDDY_LIGHTOUT_FIRST + NUM_JUMPSCARE_FREDDY_LIGHTOUT, // 11 frames
    JUMPSCARE_CHICA_FIRST = JUMPSCARE_BONNIE_FIRST + NUM_JUMPSCARE_BONNIE, // 16 frames
    JUMPSCARE_FOXY_FIRST = JUMPSCARE_CHICA_FIRST + NUM_JUMPSCARE_CHICA, // 21 frames

    OFFICE,
    LEFT_DOOR_CLOSED,
    RIGHT_DOOR_CLOSED,
    BONNIE_LEFT_DOOR,
    FOXY_LEFT_DOOR,
    FREDDY_RIGHT_DOOR,
    CHICA_RIGHT_DOOR,

    NUM_ASSETS
} xpmASSET;

/**
 * @brief Enum for animated sprites. These are sprites that have multiple frames that need to be displayed in sequence to create an animation effect, such as the animatronic jumpscares.
 */
typedef enum {
    ANIM_CAMERA_MONITOR,
    ANIM_BONNIE_JUMPSCARE,
    ANIM_CHICA_JUMPSCARE,
    ANIM_FREDDY_JUMPSCARE,
    ANIM_STATIC_SCREEN,
    NUM_ANIM_ASSETS
} AnimAsset;

/**
 * @brief Mapping of power level first digit to their corresponding sprit assets.
 */
static const xpmASSET power1_to_asset[] = {
    [1] = I_POWER1,
    [2] = I_POWER2,
    [3] = I_POWER3,
    [4] = I_POWER4,
    [5] = I_POWER5,
    [6] = I_POWER6,
    [7] = I_POWER7,
    [8] = I_POWER8,
    [9] = I_POWER9
};

/**
 * @brief Mapping of power level digits to their corresponding sprit assets for the second of the power percentage display.
 */
static const xpmASSET power2_to_asset[] = {
    [0] = II_POWER0,
    [1] = II_POWER1,
    [2] = II_POWER2,
    [3] = II_POWER3,
    [4] = II_POWER4,
    [5] = II_POWER5,
    [6] = II_POWER6,
    [7] = II_POWER7,
    [8] = II_POWER8,
    [9] = II_POWER9
};

#define CAM_EMPTY  0
#define CAM_FREDDY (1 << FREDDY)
#define CAM_BONNIE (1 << BONNIE)
#define CAM_CHICA  (1 << CHICA)
#define CAM_FOXY   (1 << FOXY)

/**
 * @brief Mapping of CAM1A states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam1a_assets[] = {
    [CAM_EMPTY] = CAM_1A_EMPTY,
    [CAM_FREDDY] = CAM_1A_FREDDY,
    [CAM_BONNIE] = CAM_1A_BONNIE,
    [CAM_CHICA] = CAM_1A_CHICA,
    [CAM_BONNIE | CAM_CHICA] = CAM_1A_BONNIE_CHICA,
    [CAM_FREDDY | CAM_BONNIE] = CAM_1A_FREDDY_BONNIE,
    [CAM_FREDDY | CAM_CHICA] = CAM_1A_FREDDY_CHICA,
    [CAM_FREDDY | CAM_BONNIE | CAM_CHICA] = CAM_1A_FREDDY_BONNIE_CHICA,
};

/**
 * @brief Mapping of CAM1B states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam1b_assets[] = {
    [CAM_EMPTY] = CAM_1B_EMPTY,
    [CAM_FREDDY] = CAM_1B_FREDDY,
    [CAM_BONNIE] = CAM_1B_BONNIE,
    [CAM_CHICA] = CAM_1B_CHICA,
    [CAM_BONNIE | CAM_CHICA] = CAM_1B_BONNIE_CHICA,
    [CAM_FREDDY | CAM_BONNIE] = CAM_1B_FREDDY_BONNIE,
    [CAM_FREDDY | CAM_CHICA] = CAM_1B_FREDDY_CHICA,
    [CAM_FREDDY | CAM_BONNIE | CAM_CHICA] = CAM_1B_FREDDY_BONNIE_CHICA,
};

/**
 * @brief Mapping of CAM2A states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam2a_assets[] = {
    [CAM_EMPTY] = CAM_2A_EMPTY,
    [CAM_BONNIE] = CAM_2A_BONNIE,
    [CAM_FOXY] = CAM_2A_FOXY,
    [CAM_BONNIE | CAM_FOXY] = CAM_2A_BONNIE_FOXY,
};

/**
 * @brief Mapping of CAM2B states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam2b_assets[] = {
    [CAM_EMPTY] = CAM_2B_EMPTY,
    [CAM_BONNIE] = CAM_2B_BONNIE,
    [CAM_FOXY] = CAM_2B_FOXY,
    [CAM_BONNIE | CAM_FOXY] = CAM_2B_BONNIE_FOXY,
};

/**
 * @brief Mapping of CAM3 states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam3_assets[] = {
    [CAM_EMPTY] = CAM_3_EMPTY,
    [CAM_BONNIE] = CAM_3_BONNIE,
};

/**
 * @brief Mapping of CAM4A states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam4a_assets[] = {
    [CAM_EMPTY] = CAM_4A_EMPTY,
    [CAM_CHICA] = CAM_4A_CHICA,
};

/**
 * @brief Mapping of CAM4B states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam4b_assets[] = {
    [CAM_EMPTY] = CAM_4B_EMPTY,
    [CAM_FREDDY] = CAM_4B_FREDDY,
    [CAM_CHICA] = CAM_4B_CHICA,
    [CAM_FREDDY | CAM_CHICA] = CAM_4B_FREDDY_CHICA,
};

/**
 * @brief Mapping of CAM5 states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam5_assets[] = {
    [CAM_EMPTY] = CAM_5_EMPTY,
    [CAM_BONNIE] = CAM_5_BONNIE,
};

/**
 * @brief Mapping of CAM6 states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
static const xpmASSET cam6_assets[] = {
    [CAM_EMPTY] = CAM_6_EMPTY,
    [CAM_FREDDY] = CAM_6_FREDDY,
    [CAM_CHICA] = CAM_6_CHICA,
    [CAM_FREDDY | CAM_CHICA] = CAM_6_FREDDY_CHICA,
};

/**
 * @brief Mapping of CAM7 states.
 * @details Each animatronic is represented by a bit in the index, so we can combine them to get the correct asset for each possible combination of animatronics in the camera view. For example, if Freddy and Bonnie are in the camera view, we can use the index CAM_FREDDY | CAM_BONNIE to get the corresponding asset from the cam1a_assets array. 
 */
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

/**
 * @brief Getter for an animated sprite represented by a specific enum value
 */
AnimSprite* get_anim_asset(AnimAsset asset);

#endif

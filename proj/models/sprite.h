#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>

/**
 *  @brief Basic sprite structure that holds basic information about the sprite now loaded from a XPM. 
 * @param width width of the sprite in pixels
 * @param height height of the sprite in pixels
 * @param map points to the pixels of the sprite 
 */
typedef struct {
    uint16_t width, height; // xpm_image_type comes in uint16_t
    uint8_t* map; 
} Sprite;

/**
 * @brief Creates a new sprite from an XPM array
 * @details Follows closely to the function given in "Lab5 & sprites with our indexation mode being XPM_8_8_8_8 following our choice of using mode 0x104C. We used Gimpo to load the XPMs so colors are represented using 3 bytes (no opacity factor) and thus we can use xpm_load without any trouble" 
 * @param xpm pointer to xpm array that represents our sprite
 * @return Pointer to the created sprite
 */
Sprite* create_sprite(xpm_map_t xpm);

/**
 * @brief Destroys the sprite object by freeing its allocated memory
 * @param sp pointer to the sprite that we want destroyed
 */
void destroy_sprite(Sprite* sp);


/**
 * @brief 
 */

#endif
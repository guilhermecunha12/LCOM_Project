#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>

/**
 *  @brief Basic sprite structure that holds basic information about the sprite now loaded from a XPM.
 * @param x // current x position of the sprite (can be negative as we'll have horizontal camera movement)
 * @param y // current y position of the
 * @param width width of the sprite in pixels
 * @param height height of the sprite in pixels
 * @param map points to the pixels of the sprite 
 */
typedef struct {
    uint16_t y;
    int x; 
    uint16_t width, height; // xpm_image_type comes in uint16_t
    uint8_t* map; 
} Sprite;

/**
 * @brief Animated sprite structure that extends the basic sprite structure by adding animation-related information.
 * @param sp pointer to the standard sprite definition
 * @param aspeed no. frames per pixmap
 * @param cur_aspeed no. frames left for the current pixmap
 * @param num_fig total number of pixmaps
 * @param cur_fig current pixmap
 * @param map array of pointers to pixmaps
 */

typedef struct{
    Sprite* sp;
    int aspeed;
    int cur_aspeed;
    int num_fig;
    int cur_fig;
    char **map;
} AnimSprite;


/**
 * @brief Creates a new sprite from an XPM array
 * @details Follows closely to the function given in "Lab5 & sprites with our indexation mode being XPM_8_8_8_8 following our choice of using mode 0x104C. We used Gimpo to load the XPMs so colors are represented using 3 bytes (no opacity factor) and thus we can use xpm_load without any trouble" 
 * @param xpm pointer to xpm array that represents our sprite
 * @return Pointer to the created sprite
 */
Sprite* create_sprite(xpm_map_t xpm, int x, uint16_t y);

/**
 * @brief Destroys the sprite object by freeing its allocated memory
 * @param sp pointer to the sprite that we want destroyed
 */
void destroy_sprite(Sprite* sp);

/**
 * @brief Function responsible for drawing the sprite onto the back buffer
 * @details As in our game the camera will be moving horizontally, we can pass values of x that might be negative thus it is an integer. Also, XPM can specify "none" values that *represent transparent pixels, we must also ignored them by checking the one *considered transparent in the XPM file
 * @param sp pointer to the sprite that we want to draw
 * @param x x-coordinate of the sprite's position
 * @param y y-coordinate of the sprite's position
 * @return 0 on success, 1 on failure
 */
int draw_sprite(const Sprite* sp);


AnimSprite *create_anim_sprite(uint8_t pic_no, char *pic1[], ...);

int animate_sprite(AnimSprite *sp);
void destroy_anim_sprite(AnimSprite *sp);


#endif

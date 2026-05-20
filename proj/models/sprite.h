#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>

// TODO: review (see LCOM slides about sprites)
// Holds the metadata about the picture
typedef struct {
    int width, height; // dimensions
    uint8_t* map; // the pixel array (TODO: correct type?)
} Sprite;

// A generic function to load an XPM into your Sprite struct
Sprite* create_sprite(xpm_map_t xpm);
void destroy_sprite(Sprite* sp);

#endif
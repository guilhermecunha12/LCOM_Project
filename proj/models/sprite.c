#include "sprite.h"
#include "../devices/video/video.h"
#include "../view/ui.h"
#include <lcom/lcf.h>

Sprite* create_sprite(xpm_map_t xpm, int x, uint16_t y){
   // Allocate space for the object 
   Sprite* sp = (Sprite *) malloc (sizeof(Sprite));
   xpm_image_t img;

   if(sp == NULL) return NULL;
   // Read the sprite pixmap
   sp->map = xpm_load(xpm,XPM_8_8_8_8,&img);
   if(sp->map == NULL){
      free(sp);
      return NULL;
   }

   // Checks if the sprite has transparency colors
   const uint32_t* map32 = (const uint32_t*) sp->map;
   sp->has_transparency = false;
   int pixels = img.width * img.height;
   for (int i = 0; i < pixels; i++) {
      if (map32[i] == TRANSPARENCY_COLOR_8_8_8_8) {
         sp->has_transparency = true;
         break;  // early exit
      }
   }

   sp->width = img.width; sp->height = img.height;
   sp->x = x; sp->y = y;

   return sp;
}

int draw_sprite(const Sprite* sp) {
    if (sp == NULL || sp->map == NULL) return 1;

    // Start x for drawing the sprite (negative x values for horizontal movement)
    int start_x = (sp->x < 0) ? -sp->x : 0; // the start x within the sprite
    int end_x = sp->width;
    if (sp->x + end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH - sp->x; // clip to within the screen bounds

    // Start y for drawing the sprite (negative y values for vertical movement)
    int start_y = (sp->y < 0) ? -sp->y : 0;
    int end_y = sp->height;
    if (sp->y + end_y > SCREEN_HEIGHT) end_y = SCREEN_HEIGHT - sp->y;

    const uint32_t* map32 = (const uint32_t*) sp->map;

    for (int i = start_y; i < end_y; i++) {

      if (sp->has_transparency) { // draw pixel by pixel, because its necessary to check if a single pixel is transparent or not

         int map_row_base = i * sp->width; // index of the first pixel of the current row

         for (int j = start_x; j < end_x; j++) {
            uint32_t color = map32[map_row_base + j];   
            if (color != TRANSPARENCY_COLOR_8_8_8_8) {
               if (vg_draw_pixel(sp->x + j, sp->y + i, color)) return 1;
            }
         }

      } else { // the sprite has not transparency colors, therefore we can draw the images by entire row at a time
         if (vg_draw_row(sp->x + start_x, sp->y + i, &map32[(i * sp->width) + start_x], end_x - start_x)) return 1;
      }
    }
    return 0;
}


// Free dinamic memory and prevent leaks
void destroy_sprite(Sprite* sp){
   if(sp == NULL) return;
   if(sp->map) free(sp->map);
   free(sp);
   // sp = NULL; (note on pwp to then change the pointer to null)
}



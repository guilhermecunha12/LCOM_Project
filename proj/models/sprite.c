#include "sprite.h"
#include "../../lab5/video.h"
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

  sp->width = img.width; sp->height = img.height;
  sp->x = x; sp->y = y;

  return sp;
}

int draw_sprite(const Sprite* sp){
   if(sp == NULL || sp->map == NULL) return 1;

   int start_x = 0;
   if(sp->x < 0) start_x = -sp->x; // If x is negative, we need to start drawing at that given offset left shift on pixmap 

   // Loop through the pixmap positions 
   for(int i=0; i<sp->height;i++){
      for(int j=start_x; j<sp->width;j++){
        // Our games camera will only move horizontally
         int shift_horizontal = sp->x + j;
        
         if(shift_horizontal < 0 || shift_horizontal >= SCREEN_WIDTH 
          ||(sp->y+i >= SCREEN_HEIGHT)) continue; 

         uint32_t color = 0;
         memcpy(&color, &sp->map[(i*sp->width + j)*BYTES_PER_PIXEL], BYTES_PER_PIXEL);

         if(color != TRANSPARENCY_COLOR_8_8_8_8) vg_draw_pixel(shift_horizontal,sp->y+i,color);
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



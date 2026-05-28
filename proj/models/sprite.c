#include "sprite.h"
#include "../../lab5/video.h"
#include "../view/ui.h"
#include <lcom/lcf.h>


Sprite* create_sprite(xpm_map_t xpm){
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

  return sp;
}

int draw_sprite(const Sprite* sp, int x, uint16_t y){
   if(sp == NULL || sp->map == NULL) return 1;

   for(int i=0; i<sp->height;i++){
      for(int j=0; j<sp->width;j++){
        // Our games camera will only move horizontally
         int shift_horizontal = x + j;
        
         if(shift_horizontal < 0 || shift_horizontal >= SCREEN_WIDTH 
          ||(y+i >= SCREEN_HEIGHT)) continue; 

         uint32_t color = 0;
         memcpy(&color, &sp->map[(i*sp->width + j)*BYTES_PER_PIXEL], BYTES_PER_PIXEL);

         if(color != TRANSPARENCY_COLOR_8_8_8_8) vg_draw_pixel(shift_horizontal,y+i,color);
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

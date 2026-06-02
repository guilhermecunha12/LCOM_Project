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

  sp->width = img.width; sp->height = img.height;
  sp->x = x; sp->y = y;

  return sp;
}

int draw_sprite(const Sprite* sp){
   if(sp == NULL || sp->map == NULL) return 1;

   char* buf = vg_get_back_buffer();
   uint16_t h_res = vg_get_h_res();
   unsigned bpp = vg_get_bytes_per_pixel();

   int start_x = (sp->x < 0) ? -sp->x : 0;

   for(int i = 0; i < sp->height; i++){
      int screen_y = sp->y + i;
      if(screen_y < 0 || screen_y >= SCREEN_HEIGHT) continue;

      for(int j = start_x; j < sp->width; j++){
         int screen_x = sp->x + j;
         if(screen_x >= SCREEN_WIDTH) break;

         uint32_t color = 0;
         memcpy(&color, &sp->map[(i * sp->width + j) * bpp], bpp);

         if(color != TRANSPARENCY_COLOR_8_8_8_8){
            unsigned pos = (screen_y * h_res + screen_x) * bpp;
            memcpy(&buf[pos], &color, bpp);
         }
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



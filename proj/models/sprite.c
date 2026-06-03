#include "sprite.h"
#include "../../lab5/video.h"
#include "../view/ui.h"
#include <stdarg.h>
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


AnimSprite *create_anim_sprite(uint8_t no_pic, int x, uint16_t y, int aspeed, xpm_map_t pic1, ...){
   AnimSprite *asp = (AnimSprite *) malloc(sizeof(AnimSprite));

   // Initialize all constructor values
   asp->map = create_sprite(pic1,0,0);
   asp->num_fig = no_pic;
   asp->cur_fig = 0;
   asp->aspeed = aspeed;
   asp->cur_aspeed = aspeed;
   asp->map =  malloc((no_pic) * sizeof(char *));
   asp -> map[0] = asp->sp->map;

   va_list ap;
   va_start(ap, pic1);

   for(int i = 0; i < no_pic; i++){
      char **tmp = va_arg(ap, char **);

      xpm_image_t img;
      asp->map[i] = xpm_load(tmp, XPM_8_8_8_8, &img);

      // Clean up in case something is wrong with dimensions or map load
      if(asp->map[i] == NULL || img.width != asp->sp->width || img.height != asp->sp->height){
         for(int j = 1; j < i; j++) free(asp->map[j]);
         free(asp->map);
         destroy_sprite(asp->sp);
         free(asp);
         va_end(ap);
         return NULL;
      }
   }

   va_end(ap);
   return asp;
}


int animate_sprite(AnimSprite *asp){
   if(asp == NULL || asp->map == NULL) return 1;

   asp->cur_aspeed--;
   if(asp->cur_aspeed == 0){
      asp->cur_fig = (asp->cur_fig + 1) % asp->num_fig; 
      asp->sp->map = asp->map[asp->cur_fig]; 
      asp->cur_aspeed = asp->aspeed;
   }

   return 0;
}




void destroy_anim_sprite(AnimSprite *asp) {
   if(asp == NULL) return;

   if(asp->map != NULL) {
      if(asp->sp != NULL) asp->sp->map = asp->map[0];

      for(int i = 1; i < asp->num_fig; i++) {
         free(asp->map[i]);
      }
      free(asp->map);
   }

   destroy_sprite(asp->sp);
   free(asp);
}



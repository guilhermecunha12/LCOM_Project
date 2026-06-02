#include <lcom/lcf.h>
#include "video.h"

static char *video_mem;
static char *back_buffer; 

static uint16_t h_res;
static uint16_t v_res;
static vbe_mode_info_t vmi;

static unsigned frame_buffer_size;
static unsigned bytes_per_pixel;


int(init_video_card)(uint16_t mode){
  if(config_Vram(mode)) return 1;
  if(initialize_back_buffer()) return 1;
  if(vg_set_mode(mode)) return 1;
  return 0;
}


int(switch_text_mode)(void){
  if(back_buffer != NULL) {
    free(back_buffer);
    back_buffer = NULL;
  }
  return vg_exit() ? 1 : 0;
}


enum xpm_image_type(get_color_mode)(){
  // Switch between the provided bits per pixel (as they mape to unique colors formats)
  switch(vmi.BitsPerPixel){
    case 8: return XPM_INDEXED;
    case 15: return XPM_1_5_5_5;
    case 16: return XPM_5_6_5;
    case 24: return XPM_8_8_8;
    case 32: return XPM_8_8_8_8;
    default:
      return INVALID_XPM;
  }
}

int(draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

    xpm_image_t img;
    uint8_t *pixmap;

    enum xpm_image_type color_format = get_color_mode();
    if(color_format == INVALID_XPM) return 1;

    pixmap = xpm_load(xpm,color_format,&img);
    // Should contain the address of the allocated memory for the Pixmap
    if(pixmap == NULL) return 1;

    // Traverse the 2D map normally and draw each pixel
    for(int i=0; i<img.height;i++){
        for(int j=0; j<img.width;j++){
          uint32_t colour =0;
          // In direct mode each pixel stores directly its corresponding colour 
          memcpy(&colour, &pixmap[(i*img.width +j)*bytes_per_pixel],bytes_per_pixel);
          
          if(vg_draw_pixel(x+j,y+i,colour)){
            free(pixmap);
            return 1;

          } 
        }
    }

    free(pixmap);
    return 0;
}


int config_Vram(uint16_t mode){
  if(vbe_get_mode_info(mode, &vmi) != 0) {
    return 1;
  }

  // Store the horizontl and vertical resolutions in global variables
  h_res = vmi.XResolution;
  v_res = vmi.YResolution;

  // It uses a + 7 to round up. for example if in mode 0x110 we have 15 bits per pixel, we need 2 bytes to store the color of a pixel. If we just did 15 / 8, we would get 1 byte per pixel, which is not enough to store all the colors of the mode.

  bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;

  // Set the base address of the vram and its size
  unsigned int frame_buffer_base = vmi.PhysBasePtr;
  frame_buffer_size = h_res * v_res * bytes_per_pixel;

  /* Grant memory mapping permissions */
  struct minix_mem_range mr;
  mr.mr_base = (phys_bytes) frame_buffer_base;
  mr.mr_limit = mr.mr_base + frame_buffer_size;  

  int r;
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) return 1;

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, frame_buffer_size);
  if(video_mem == MAP_FAILED) return 1;
  return 0;
}


int vg_set_mode(uint16_t mode){
  reg86_t reg; // structure that will have the values to be loaded into the CPU registers before executing the BIOS function call
  memset(&reg, 0, sizeof(reg)); // set reg86_t reg to zeros

  reg.intno = VIDEO_INTNO; 		// Must invoke VBE function via INT 0x10 (software interrupt)
  reg.ah = VBE_CALL_AH; 			// To invoke a VBE function, AH register should be 0x4F
  reg.al = VBE_SET_MODE_FUNCTION; // VBE function being called is specified in the AL register.

  reg.bx = mode; // the mode should be placed in the BX register
  reg.bx |= BIT(14); // set Bit 14 to use linear frame buffer model
  reg.bx &= ~BIT(15); // unset Bit 15 so that the display memory is cleared after switching to the desired graphics mode

  // kernel call that switches to real mode (memory addresses map directly to physical RAM locations), makes a BIOS function call (in this case a VBE function call) and switches back to protected mode 
  if (sys_int86(&reg) != OK) return 1; 

  // Check VBE function call completion status (section 4.1. of https://www.phatcode.net/res/221/files/vbe20.pdf)
  if (reg.ah != FUNCTION_CALL_SUCCESS || reg.al != SUPPORTED_FUNCTION) return 1;

  return 0;
}


int initialize_back_buffer(){
    if(back_buffer != NULL) return 0; 

    back_buffer = malloc(frame_buffer_size);
    if(back_buffer == NULL) return 1;

    // Initializes back buffer from the info extracted of our    current mode
    memset(back_buffer, 0, frame_buffer_size);
    return 0;
}

void swap_buffers(){
    if(back_buffer == NULL) return;
    memcpy(video_mem,back_buffer, frame_buffer_size);
}

void clear_back_buffer(){
    if(back_buffer == NULL) return;
    memset(back_buffer, 0, frame_buffer_size);
}

int vg_draw_pixel (uint16_t x, uint16_t y, uint32_t color) {
  // Check if coordinates are within the screen limits
  if(x > h_res || y > v_res) return 1;
  // Caculate the position in VRAM of the pixel to be drawn 
  unsigned position = ((y * h_res) + x) * bytes_per_pixel;
  // Copy memory from color to back buffer position. This couls be done trough a for loop.
  if (memcpy(&back_buffer[position], &color, bytes_per_pixel) == NULL) return 1;
  return 0;
}

int (vg_draw_hline) (uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  // Draw a horizontal line by drwaing pixel by pixel, len times
  for(unsigned x_off = 0; x_off < len; x_off++){
    if(vg_draw_pixel(x + x_off, y, color)) return 1;
  }
  return 0;
}



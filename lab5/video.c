#include <lcom/lcf.h>
#include "video.h"

static char *video_mem;

static uint16_t h_res;
static uint16_t v_res;
static vbe_mode_info_t vmi;
static unsigned bytes_per_pixel;

void* (vg_init) (uint16_t mode) {
  // Get the mode info struct for the specified mode
  if(vbe_get_mode_info(mode, &vmi) != 0) {
    return NULL;
  }

  // Store the horizontl and vertical resolutions in global variables
  h_res = vmi.XResolution;
  v_res = vmi.YResolution;

  // It uses a + 7 to round up. for example if in mode 0x110 we have 15 bits per pixel, we need 2 bytes to store the color of a pixel. If we just did 15 / 8, we would get 1 byte per pixel, which is not enough to store all the colors of the mode.

  bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;

  // Set the base address of the vram and its size
  unsigned int frame_buffer_base = vmi.PhysBasePtr;
  unsigned int frame_buffer_size = h_res * v_res * bytes_per_pixel;

  /* Grant memory mapping permissions */
  struct minix_mem_range mr;
  mr.mr_base = (phys_bytes) frame_buffer_base;
  mr.mr_limit = mr.mr_base + frame_buffer_size;  

  int r;
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    return NULL;

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, frame_buffer_size);

  if(video_mem == MAP_FAILED)
    return NULL;


  // then set the mode similiar to vidoe_test_init
  reg86_t reg;
  memset(&reg, 0, sizeof(reg));

  reg.intno = VIDEO_INTNO;
  reg.ah = VBE_CALL_AH;
  reg.al = VBE_SET_MODE_FUNCTION;

  reg.bx = mode;
  reg.bx |= BIT(14);
  reg.bx &= ~BIT(15);

  if(sys_int86(&reg) != OK) 
    return NULL;

  if(reg.ah != FUNCTION_CALL_SUCCESS || reg.al != SUPPORTED_FUNCTION) 
    return NULL;

  return video_mem;
}

int vg_draw_pixel (uint16_t x, uint16_t y, uint32_t color) {
  // Check if coordinates are within the screen limits
  if(x > h_res || y > v_res) return 1;
  // Caculate the position in VRAM of the pixel to be drawn 
  unsigned position = ((y * h_res) + x) * bytes_per_pixel;
  // Copy memory from color to VRAM position. This couls be done trough a for loop.
  if (memcpy(&video_mem[position], &color, bytes_per_pixel) == NULL) return 1;

  return 0;
}

int (vg_draw_hline) (uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  // Draw a horizontal line by drwaing pixel by pixel, len times
  for(unsigned x_off = 0; x_off < len; x_off++){
    if(vg_draw_pixel(x + x_off, y, color)) return 1;
  }

  return 0;
}

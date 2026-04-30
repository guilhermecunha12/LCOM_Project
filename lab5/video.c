#include <lcom/lcf.h>
#include "video.h"

static char *video_mem;

static uint16_t h_res;
static uint16_t v_res;


static char *video_mem;          /* Virtual address to which VRAM is mapped */
static vbe_mode_info_t vmi;      /* VBE mode info */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */

int vg_set_mode(uint16_t mode){
  reg86_t reg;
  memset(&reg,0,sizeof(reg));

  // BIOS Video Card Interrupt Vector 
  reg.intno = VIDEO_INTNO ;
  // Set VBE Mode
  reg.ah = VBE_CALL_AH;
  reg.al = VBE_SET_MODE_FUNCTION;
  // Mode is passed to register bx with bit 14 set
  reg.bx = BIT(14) | mode;
  return sys_int86(&reg);
}

int config_Vram(uint16_t mode){

  int r;
  struct minix_mem_range mr;
  unsigned int vram_base;          /* VRAM's physical addresss */
  unsigned int vram_size;          /* VRAM's size, but you can use the frame-buffer size */

  // Initialize vmi with extracted vbi mode info
  if(vbe_get_mode_info(mode,&vmi)) return 1;

  h_res = vmi.XResolution;
  v_res = vmi.YResolution;
  // Edge case in mode 0x110 (applied here generally)
  bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;
  // Set vram_base and vram_size according to VBE mode information
  vram_base = vmi.PhysBasePtr;
  vram_size =  vmi.XResolution * vmi.YResolution * bytes_per_pixel ;
  /* Grant memory mapping permissions */
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size; 
  
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

  return 0;
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



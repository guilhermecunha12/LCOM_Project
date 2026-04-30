#ifndef VIDEO_H
#define VIDEO_H

#include <lcom/lcf.h>

#define VIDEO_INTNO             0x10 // Interrupt number used by the BIOS’ video services.
#define VBE_CALL_AH             0x4F // Value of AH register to invoke a VBE function.
#define VBE_SET_MODE_FUNCTION   0x02 // VBE Set Mode function, to be specified in the AL register.

// VBE Return Status related

#define SUPPORTED_FUNCTION      0x4F // Return status of AL register that indicates that the VBE function is supported.
#define FUNCTION_CALL_SUCCESS   0x00 // Return status of AH register that indicates that the VBE function call was successful.

void* (vg_init) (uint16_t mode);

int vg_draw_pixel (uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline) (uint16_t x, uint16_t y, uint16_t len, uint32_t color);



#endif

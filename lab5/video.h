#ifndef VIDEO_H
#define VIDEO_H

#include <lcom/lcf.h>

#define VIDEO_INTNO             0x10 // Interrupt number used by the BIOS’ video services.
#define VBE_CALL_AH             0x4F // Value of AH register to invoke a VBE function
#define VBE_SET_MODE_FUNCTION   0x02 // VBE Set Mode function, to be specified in the AL register


#endif

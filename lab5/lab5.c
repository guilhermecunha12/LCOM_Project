// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>
#include "video.h"
#include "../lab3/kbc.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab5/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

// Example of modes to test with (hex): 105, 110, 115, 11A, 14C
int(video_test_init)(uint16_t mode, uint8_t delay) {

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
	
	if (sleep(delay)) return 1; // wait 'delay' seconds before returning to text mode
	
	if(vg_exit()) return 1; // LCF function to return to Text Mode

    return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
     
    // Call vg_init. It will map the Vram memory to the process logicla memory and initiliaze mode, respectly.
    if(vg_init(mode) == NULL) return 1;

    // Draw the rectangle by drawing horizontal lines height times
    for(unsigned y_off = 0; y_off < height; y_off++) {
        if(vg_draw_hline(x, y + y_off, width, color)){
            vg_exit();
            return 1;
        }
    }

    // Subscribe to the keyboard interrupts to wait for the ESC breakcode to exit the graphics mode
    uint8_t bit_no = 1;
    if(kbd_subscribe_int(&bit_no)) return 1;
    uint8_t scancode;
    int ipc_status;
    message msg;
    int r;
    do {
        if ((r = driver_receive(ANY, &msg, &ipc_status))   != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        } 
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    kbc_ih();
                    scancode = get_scancode();
                    break;
                default:
                    break;
            }
        }
    } while (scancode != ESC_BREAKCODE);

    // Unsubscribe keyboard interrupts and return to text mode
    if(kbd_unsubscribe_int()) {
        vg_exit();
        return 1;
    }
    
    // Return to text mode
    if(vg_exit()) return 1;

    return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
    /* To be completed */
    printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

    return 1;
}

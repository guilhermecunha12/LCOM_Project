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

	if(vg_set_mode(mode)) return 1;
	
	if (sleep(delay)) return 1; // wait 'delay' seconds before returning to text mode
	
	if(vg_exit()) return 1; // LCF function to return to Text Mode

    return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
     
    // Call vg_init. It will map the Vram memory to the process logicla memory and initiliaze mode, respectly.
    if(init_video_card(mode)) return 1;
    clear_back_buffer();

    // Draw the rectangle by drawing horizontal lines height times
    for(unsigned y_off = 0; y_off < height; y_off++) {
        if(vg_draw_hline(x, y + y_off, width, color)){
            vg_exit();
            return 1;
        }
    }

    swap_buffers();

    // Subscribe to the keyboard interrupts to wait for the ESC breakcode to exit the graphics mode
    uint8_t bit_no = 1;
    if(kbd_subscribe_int(&bit_no)) return 1;
    uint8_t scancode = 0;
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
                    if (msg.m_notify.interrupts & bit_no && process_scancode()) {
                        scancode = get_scancode()[1];
                    }
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
    // We should switch to VBE mode 0x105
    if(init_video_card(0x105)) return 1;
    clear_back_buffer();

    if (draw_xpm(xpm, x, y)) return 1;

    swap_buffers();

    // Subscribe to the keyboard interrupts to wait for the ESC breakcode to exit the graphics mode
    uint8_t bit_no = 1;
    if(kbd_subscribe_int(&bit_no)) return 1;
    uint8_t scancode = 0;
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
                    if (msg.m_notify.interrupts & bit_no && process_scancode()) {
                        scancode = get_scancode()[1];
                    }
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

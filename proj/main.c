 #include <lcom/lcf.h>

// Device header files
#include "../lab4/mouse.h"
#include "../lab3/kbc.h"

#include "state.h"
#include "controller/controller.h"
#include "view/view.h"


int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/proj/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

void init_game_state(GameState* state) {
    state->type = MAIN_MENU;
    state->global_data.current_night = 0; // not started yet
    // TODO: initialize mouse coordinates in global data
    state->data.main_menu.selected_option = 0; // first option selected
}


int(proj_main_loop)(int argc, char* argv[]) {
    uint8_t timer_irq_set, kbd_irq_set, mouse_irq_set; // bitmasks for each IRQ; TODO: initialize them
    if (general_subscribe()) return 1;

    GameState current_state;
    GameEvent current_event;

    init_game_state(&current_state);
    load_all_assets(); // TODO: review - Parses all XPMs into Sprite structs in RAM

    int ipc_status, r;
    message msg;
    
    while (current_state.type != EXIT) {

        if ((r = driver_receive(ANY, &msg, &ipc_status))   != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        } 
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:

                    // Timer interrupt
                    if (msg.m_notify.interrupts & timer_irq_set) {
                        timer_int_handler(); // TODO: create a more readable function? There is no timer.h in lab2.
                        current_event.type = TIMER_TICK;
                        current_event.data.timer_ticks = get_counter();

                        process_event(&current_state, &current_event); // TODO: process_event will run game logic based on the current state and the current event. This function can modify the current state.

                        // Only render the screen on timer tick to ensure consistent frame rate.
                        render_frame(&current_state);
                    }

                    // Keyboard interrupt
                    if (msg.m_notify.interrupts & kbd_irq_set) {
                        if (process_scancode()) { // implement in kbc.c

                            if (is_keyboard_press()) { // TODO: implement in kbc.c
                                current_event.type = KEYBOARD_PRESS;
                            } else {
                                current_event.type = KEYBOARD_RELEASE; // TODO: needed?
                            }

                            current_event.data.scancode = get_scancode(); // TODO: this function only returns the last byte read, check if we need to return the whole scancode (2 bytes) in case of 2-byte scancodes (like arrow keys)
                            
                            process_event(&current_state, &current_event);
                        }
                    }

                    // Mouse interrupt
                    if (msg.m_notify.interrupts & mouse_irq_set) {
                        if (process_packet()) {
                            // TODO: maybe clear the current_event variable at the beginning of each interrupt?
                            if (is_mouse_click()) {
                                current_event.type = MOUSE_LB_CLICK;
                                current_event.data.mouse_coords.delta_x = 0;
                                current_event.data.mouse_coords.delta_y = 0;

                            } else if (is_mouse_move()) {
                                current_event.type = MOUSE_MOVE;

                                struct packet current_packet = get_mouse_packet();
                                current_event.data.mouse_coords.delta_x = current_packet.delta_x;
                                current_event.data.mouse_coords.delta_y = current_packet.delta_y;
                            }
                            
                            // only process left button clicks or mouse movements.
                            if (current_event.type == MOUSE_LB_CLICK || current_event.type == MOUSE_MOVE) {
                                process_event(&current_state, &current_event);
                            }
                        }                        
                    }
                    break;
                default:
                    break;
            }
        }
    }

    unload_all_assets(); // TODO: review - Frees the heap memory cleanly before Minix exits
    if (general_unsubscribe()) return 1;
    return 0;
}
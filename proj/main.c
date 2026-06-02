 #include <lcom/lcf.h>

// Device header files
#include "devices/subscribe.h"

#include "state.h"
#include "controller/controller.h"
#include "view/view.h"
#include "devices/event_updater.h"
#include "models/assets.h"

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
    
    // Initialization of the main menu considering the current night
    state->data.main_menu = init_main_menu(state->global_data.current_night);
    
    state->global_data.background_offset_x = 0; // Start with no background offset
}


int(proj_main_loop)(int argc, char* argv[]) {
  
    uint8_t timer_irq_set = IRQ_TIMER;
    uint8_t kbd_irq_set = IRQ_KBD;
    uint8_t mouse_irq_set = IRQ_MOUSE;
    uint16_t vbe_mode = 0x14C; 

    if (subscribe_devices(&timer_irq_set, &kbd_irq_set, &mouse_irq_set, vbe_mode)) return 1;

    GameState* current_state = (GameState*) malloc(sizeof(GameState));
    GameEvent* current_event = (GameEvent*) malloc(sizeof(GameEvent));

    init_game_state(current_state);
    load_all_assets(); // TODO: review - Parses all XPMs into Sprite structs in RAM

    int ipc_status, r;
    message msg;
    
    while (current_state->type != EXIT) {
        if ((r = driver_receive(ANY, &msg, &ipc_status))   != 0 ){ 
          printf("driver_receive failed with: %d", r);
          continue;
        } 
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    // Timer interrupt
                    if (msg.m_notify.interrupts & timer_irq_set) {
                        if(update_timer_game_event(current_event) == 0) {
                            process_event(current_state, current_event); 
                            // Only render the screen on timer tick to ensure consistent frame rate.
                            render_frame(current_state);
                            printf("Timer tick: %lu\n", current_event->data.timer_ticks); // Debug: print the number of timer ticks
                        }
                    }

                    // Keyboard interrupt
                    if (msg.m_notify.interrupts & kbd_irq_set) {
                        if (update_keyboard_game_event(current_event) == 0) { // if the scancode was successfully processed into a game event
                            process_event(current_state, current_event);
                        }
                    }

                    // Mouse interrupt
                    if (msg.m_notify.interrupts & mouse_irq_set) {
                        if(update_mouse_game_event(current_event) == 0) {
                            // only process left button clicks or mouse movements.
                            if (current_event->type == MOUSE_LB_CLICK || current_event->type == MOUSE_MOVE) {
                                process_event(current_state, current_event);
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
    if (unsubscribe_devices()) return 1;
    return 0;
}

#include <lcom/lcf.h>

// Device header files
#include "devices/subscribe.h"

#include "state.h"
#include "controller/controller.h"
#include "view/view.h"
#include "devices/event_updater.h"
#include "models/assets.h"
#include "devices/serial_port/serial_port.h"

#include "view/ui.h"

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    //lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

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

/** 
 * @brief Initializes the game state to the main menu and sets up the global data.
 * @param state Pointer to the GameState struct to initialize.
 */
void init_game_state(GameState* state) {
    state->global_data.current_night = 0;
    state->global_data.mouse_x = SCREEN_WIDTH / 2;
    state->global_data.mouse_y = SCREEN_HEIGHT / 2;
    state->global_data.background_offset_x = 0;
    init_main_menu(state);
}


int receiver_main_loop() {

    uint8_t timer_irq_set = IRQ_TIMER;
    uint8_t kbd_irq_set = IRQ_KBD;
    uint8_t com1_irq_set = IRQ_COM1;
    uint16_t vbe_mode = VBE_MODE;
    
    if (subscribe_receiver_devices(&timer_irq_set, &kbd_irq_set, &com1_irq_set, vbe_mode)) return 1;

    GameState* current_state = (GameState*) malloc(sizeof(GameState));
    GameEvent* current_event = (GameEvent*) malloc(sizeof(GameEvent));

    current_state->type = WAITING_FOR_DATA;

    load_receiver_assets();
    render_frame(current_state);
    
    int ipc_status, r;
    message msg;

    while (current_state->type != EXIT) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) { 
          printf("driver_receive failed with: %d", r);
          continue;
        } 
        
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    
                    // Timer interrupt
                    if (msg.m_notify.interrupts & timer_irq_set) {
                        if(update_timer_game_event(current_event) == 0) {
                            render_frame(current_state);
                        }
                    }

                    // Keyboard interrupt
                    if (msg.m_notify.interrupts & kbd_irq_set) {
                        if (update_keyboard_game_event(current_event) == 0) {
                            process_event(current_state, current_event);
                        }
                    }

                    // COM1 interrupt
                    if (msg.m_notify.interrupts & com1_irq_set) {
                        if (update_serial_port_game_event(current_event) == 0) {
                            process_event(current_state, current_event);
                        }
                    }

                    break;

                default:
                    break;
            }
        }
    }

    unload_all_assets(); // TODO: review - Frees the heap memory cleanly before Minix exits
    if (unsubscribe_receiver_devices()) return 1;
    return 0;
}

int(proj_main_loop)(int argc, char* argv[]) {

    if (argc >= 1 && strcmp(argv[0], "receiver") == 0) {
        return receiver_main_loop();
    }

    uint8_t timer_irq_set = IRQ_TIMER;
    uint8_t kbd_irq_set = IRQ_KBD;
    uint8_t mouse_irq_set = IRQ_MOUSE;
    uint8_t com1_irq_set = IRQ_COM1;
    uint16_t vbe_mode = VBE_MODE; 

    if (subscribe_devices(&timer_irq_set, &kbd_irq_set, &mouse_irq_set, &com1_irq_set, vbe_mode)) return 1;

    GameState* current_state = (GameState*) malloc(sizeof(GameState));
    GameEvent* current_event = (GameEvent*) malloc(sizeof(GameEvent));

    init_game_state(current_state);
    load_all_assets();

    int ipc_status, r;
    message msg;
    
    while (current_state->type != EXIT) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) { 
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
                        }
                    }

                    // Keyboard interrupt
                    if (msg.m_notify.interrupts & kbd_irq_set) {
                            
                        if (update_keyboard_game_event(current_event) == 0) {
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

    unload_all_assets();
    if (unsubscribe_devices()) return 1;
    return 0;
}

// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "../lab2/timer_count.h"
#include "../lab3/kbc.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (mouse_test_packet)(uint32_t cnt) {
  int ipc_status;
  message msg;
  int r; // return value of the driver_receive function
  
  uint8_t bit_no = 2; // index position in the bitmask msg.m_notify.interrupts

  if(enable_mouse_data_reporting()){
    return 1;
  }

  if(mouse_subscribe_int(&bit_no)){
    disable_mouse_data_reporting();
    return 1;
  }

  struct packet pp;
  int byte_index = 0; // byte index of the current mouse byte
  bool x_sign_bit = 0;
  bool y_sign_bit = 0;

  while (cnt) {
  /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }

    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: /* hardware interrupt notification */
            if (msg.m_notify.interrupts & bit_no) { /*subscribed interrupt */
              mouse_ih(); // note: if there is a read failure here, the old value of mouse_byte will be treated as the new packet byte in the next line (maybe add a static variable that would indicate an error, like if it was a return value)
              uint8_t mouse_byte = get_mouse_byte();
              
              // naive way to find out the beggining of data packets (however it only checks the 3rd bit when it is actually waiting for the first byte, ie, byte_index == 0)
              if (byte_index == 0 && (mouse_byte & BIT(3))) { // the 3rd bit of the first packet byte is always 1
                byte_index = 1; // next interrupt byte index
                pp.bytes[0] = mouse_byte;

                // populate pp struct and sign bits variables
                parse_first_byte(&pp, &x_sign_bit, &y_sign_bit, mouse_byte);

                continue; // do nothing more..
              }
              // ...not the first byte from here on

              if (byte_index == 1) {
                pp.bytes[1] = mouse_byte;
                pp.delta_x = get_delta(x_sign_bit, mouse_byte);

                byte_index++; // next byte index

              } else if (byte_index == 2) {
                pp.bytes[2] = mouse_byte;
                pp.delta_y = get_delta(y_sign_bit, mouse_byte);
              
                byte_index = 0; // reset byte_index
                
                mouse_print_packet(&pp);
                cnt--; // one less packet to go
              }
            }
            break;

        default: break; /* no other notifications expected: do nothing */
      }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
  }

  if(mouse_unsubscribe_int()){
    disable_mouse_data_reporting();
    return 1;
  }

  if(disable_mouse_data_reporting()){
    return 1;
  }

  return 0;
}


int (mouse_test_async)(uint8_t idle_time) {
  // Same structure as in previous labs to handle specific device interrupts 
    int ipc_status;
    message msg;

    uint8_t timer0_int_bit = 1;
    uint8_t mouse_int_bit = 2;

    struct packet pp;
    int byte_index = 0;
    bool x_sign_bit = 0;
    bool y_sign_bit = 0; 

    if(enable_mouse_data_reporting()){
      return 1;
    }
    
    if(timer_subscribe_int(&timer0_int_bit)){
      disable_mouse_data_reporting();
      return 1;
    }

    if(mouse_subscribe_int(&mouse_int_bit)){
      disable_mouse_data_reporting();
      timer_unsubscribe_int();
      return 1;
    } 

    int r;

    // Subscribes and handles interrupts

    
    do{
      
      if((r = driver_receive(ANY,&msg,&ipc_status)) !=0){
          printf("driver_receive failed with: %d\n", r);
          continue;
      }

      if(is_ipc_notify(ipc_status)){
          switch(_ENDPOINT_P(msg.m_source)){
              case HARDWARE:
                if(msg.m_notify.interrupts & timer0_int_bit){
                    timer_int_handler(); // Timer0 interrupt handler
                }

                if(msg.m_notify.interrupts & mouse_int_bit){
                    mouse_ih();
                    uint8_t mouse_byte = get_mouse_byte();
                    
                    if (byte_index == 0 && (mouse_byte & BIT(3))) {
                      byte_index = 1;
                      pp.bytes[0] = mouse_byte;
                      parse_first_byte(&pp, &x_sign_bit, &y_sign_bit, mouse_byte);
                      continue;
                    }
                    
                    if (byte_index == 1) {
                      pp.bytes[1] = mouse_byte;
                      pp.delta_x = get_delta(x_sign_bit, mouse_byte);
                      byte_index++;
                    } 
                    else if (byte_index == 2) {
                      pp.bytes[2] = mouse_byte;
                      pp.delta_y = get_delta(y_sign_bit, mouse_byte);
                      byte_index = 0;
                      mouse_print_packet(&pp);
                      set_counter(0); // reset the counter when we arrive at a full data packet
                    }
                }
                break;

              default:
                  break;
          }
      }

      else {}

    } while(((uint32_t)(get_counter()) < idle_time * sys_hz())); // determine the interrupt frequency of timer0 with kernell call sys_hz (lab report)

    if(mouse_unsubscribe_int()){
      disable_mouse_data_reporting();
      timer_unsubscribe_int();
      return 1;
    }

    if(timer_unsubscribe_int()){
      disable_mouse_data_reporting();
      return 1;
    }

    if(disable_mouse_data_reporting()){
      return 1;
    }

    return 0;
}

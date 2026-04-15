// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include "mouse.h"

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

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
  
  // By default, Minix does not enable data reports
  mouse_enable_data_reporting(); // TODO: implement this functionally ourselves

  uint8_t bit_no = 12; // index position in the bitmask msg.m_notify.interrupts
  if (mouse_subscribe_int(&bit_no)) return 1; // bit_no is now the mask 000....010

  struct packet pp;
  uint8_t packet_bytes[3]; // the bytes of the packet
  int byte_index = 0; // byte index of the current mouse byte
  int x_sign_bit = 0;
  int y_sign_bit = 0;

  do {
      /* Get a request message. */
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
      }

      if (is_ipc_notify(ipc_status)) { /* received notification */
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                  if (msg.m_notify.interrupts & bit_no) { /*subscribed interrupt */
                    mouse_ih();
                    uint8_t mouse_byte = get_mouse_byte();
                    
                    // naive way to find out the beggining of data packets
                    if (mouse_byte && BIT(3)) { // the 3rd bit of the first packet byte is always 1
                      byte_index = 1; // next interrupt byte index
                      packet_bytes[0] = mouse_byte;

                      // parse first byte bits, populating the packet variable
                      pp.lb = mouse_byte & BIT(1);
                      pp.rb = mouse_byte & BIT(2);
                      pp.mb = mouse_byte & BIT(3);
                      x_sign_bit = mouse_byte & BIT(4);
                      y_sign_bit = mouse_byte & BIT(5);
                      pp.x_ov = mouse_byte & BIT(6);
                      pp.y_ov = mouse_byte & BIT(7);

                      continue; // do nothing more..
                    }

                    // ...not the first byte from here on
                    if (byte_index == 1) {
                      packet_bytes[1] = mouse_byte;
                      
                      int16_t x_movement = 0;
                      if (x_sign_bit) x_movement |= BIT(9);
                      x_movement |= mouse_byte; // I think this will work
                      
                      // interpret the number in 2's complement
                      x_movement << 7;
                      x_movement >> 7; // arithmetic shift

                      pp.delta_x = x_movement;
                      byte_index++; // next byte index

                    } else if (byte_index == 2) {
                      packet_bytes[2] = mouse_byte;
                      
                      int16_t y_movement = 0;
                      if (y_sign_bit) y_movement |= BIT(9);
                      y_movement |= mouse_byte; // I think this will work
                      
                      // interpret the number in 2's complement
                      y_movement << 7;
                      y_movement >> 7; // arithmetic shift

                      pp.delta_y = y_movement;
                      byte_index = 0; // reset byte_index

                      mouse_print_packet(&pp);
                      cnt--; // one less packet to go
                    }
                  }
                  break;
              default:
                  break; /* no other notifications expected: do nothing */
          }
      } else { /* received a standard message, not a notification */
          /* no standard messages expected: do nothing */
      }
  } while (cnt); // while there are still packets to read and display
  
  if (mouse_unsubscribe_int()) return 1;

  mouse_disable_data_reporting(); // TODO: implement

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}
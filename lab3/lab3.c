#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "kbc.h"

#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


   
int(kbd_test_scan)() {
  #include <lcom/lcf.h>

  int ipc_status;
  message msg;
  int r; // return value of the driver_receive function
  set_scancode(0); // initial value, just not to leave it undefined
  uint8_t bit_no = 1; // index position in the bitmask msg.m_notify.interrupts
  bool second_byte = false; // flag that will be used in case the read scancode has two bytes

  if (kbd_subscribe_int(&bit_no)) return 1; // bit_no is now the mask 000....010

  uint8_t scancode = get_scancode();
  while( scancode != ESC_BREAKCODE ) { /* loop terminates with the breakcode of the ESC key (0x81) */
      /* Get a request message. */
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
      }
      if (is_ipc_notify(ipc_status)) { /* received notification */
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                  if (msg.m_notify.interrupts & bit_no) { /* subscribed interrupt */

                    if (second_byte) { // we are reading the second byte of the scancode
                      kbc_ih(); // IRQ 1 line was ALSO raised for the second byte
                      scancode = get_scancode();

                      uint8_t size = 2;

                      uint8_t bytes[2]; // 2-bytes read
                      bytes[0] = TWO_BYTE_PREFIX; // the byte read in the previous IRQ 1 line raise
                      bytes[1] = scancode; // last scancode read
                      
                      bool make; // if MSB of the scancode == 0, it's a makecode; else if MSB == 1, it's a breakcode
                      if (MSB(scancode)) make = false;
                      else make = true;
                      
                      kbd_print_scancode(make, size, bytes);
                      second_byte = false; // reset the flag

                    } else { // not reading the second byte of a scancode

                      kbc_ih(); // IRQ 1 line was raised, so the interrupt handler is called to get the scancode
                      scancode = get_scancode();

                      if (scancode == TWO_BYTE_PREFIX) { // if this is true, the scancode we are reading has 2 bytes
                        second_byte = true; // in the next IRQ 1 line raise, the second byte of the scancode will be read
                        // do nothing more, only print in the next iteration (IRQ 1 line raise)

                      } else {
                        uint8_t size = 1; // the scancode will have 1 byte

                        uint8_t bytes[1]; // 1 byte read
                        bytes[0] = scancode;

                        bool make; // if MSB of the scancode == 0, it's a makecode; else if MSB == 1, it's a breakcode
                        if (MSB(scancode)) make = false;
                        else make = true;

                        kbd_print_scancode(make, size, bytes);
                      }
                    }
                  }
                  break;
              default:
                  break; /* no other notifications expected: do nothing */
          }
      } else { /* received a standard message, not a notification */
          /* no standard messages expected: do nothing */
      }
  }

  if (kbd_unsubscribe_int()) return 1;

  return 0;
}


int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

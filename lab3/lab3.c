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
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_poll)() {
  // Since we will be using a while loop the variable will be initialized during the first iteration
  uint8_t code;
  // Polling loop
  do {
    // scancode will contain each key's scancode
    // In this case we must check for the function to be returning 0 since the we can only consider the output buffer data when the return is valid (indicating that data there should be read)
    if(read_KBC_output_buf(KBC_OB, &code) == 0){
      // if scancode && BREAKCODE == 1 -> makeval = false
      // if scancode && BREAKCODE == 0 -> makeval = true
      bool makeval = !(code & BREAKCODE);
      // Check if we have a situation where the scan code has 2 bytes
      // Two byte long is 0xEO: if the first scancode is this one, the value has 2 bytes
      if(code == TWO_BYTE_LONG){
        // Read the second byte of the scan code
        uint8_t second_byte;
        if(read_KBC_output_buf(KBC_OB, &second_byte) == 0){
          // The makeval will correspond to the most significant bit of the second byte
          makeval = !(second_byte & BREAKCODE);
          // Create the array for printing purposes with the first byte (E0) and then the second byte
          uint8_t bytes[2] = {code, second_byte};
          kbd_print_scancode(makeval, 2, bytes);
        }
      }
      else{
        kbd_print_scancode(makeval, 1, &code);
      }
    } 
  } while(code != ESC_BREAKCODE);

  return reset_interrupts();
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

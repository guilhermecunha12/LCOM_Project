#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

// Global variable to count the number of identified interrupts
int global_counter = 0;


int (timer_set_frequency)(uint8_t timer, uint32_t freq) { 
  int target_port = TIMER_0 + timer;
  uint8_t status_byte;
  timer_get_conf(timer,&status_byte);
  uint8_t control_byte =  (timer << 6) | TIMER_LSB_MSB | (status_byte & 0x0F); // build control byte to configure our timer

  if(sys_outb(TIMER_CTRL,control_byte)) return 1; // write control_byte to control_register

  uint16_t divider = TIMER_FREQ / (uint16_t) freq;
  uint8_t lsb, msb; 
  // Write in the specified order defined in the control byte (LSB followed by MSB)
  util_get_LSB(divider,&lsb);
  util_get_MSB(divider,&msb);

  if(sys_outb(target_port,lsb)!=0 || sys_outb(target_port,msb)!=0) return 1;
 
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  global_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  // Build the Read-Back command
  uint8_t read_back_command = 0;
  // Indicate that we are going to perform a read-back command
  read_back_command |= TIMER_RB_CMD; 

  // Since we want to read the status byte, we must set the bit that allows reading the counter 
  // and keep the bit associated with the Programmed Mode at 0, because this feature works as 
  // "enabled when low" — functionality active when the bit is 0
  read_back_command |= TIMER_RB_COUNT_;
  
  // Select the counter of the specified timer
  read_back_command |= TIMER_RB_SEL(timer);

  // Write to the control register - with error handling
  // If the return value is 1, perform an early return indicating an error
  if (sys_outb(TIMER_CTRL, read_back_command)) {
    return 1;
  }

  // Add the timer number to the base port address of the first timer to get the correct port address
  int port = 0x40 + timer; 
  // Read the status byte from the correct port and store it at the address where the status byte will be saved
  // Error handling, same as in the outb case
  if (util_sys_inb(port, st)) {
    return 1;
  }

  return 0;
}


int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  timer_get_conf(timer, &st);
  union timer_status_field_val conf;

  // field says what to display in the conf
  switch(field){
    case tsf_all:
      /* Display status byte, in hexadecimal */
      conf.byte = st;
      break;

    case tsf_initial:
      /* Display the initialization mode only */
      // Extract the Initialization Mode bits and shift them to convert to int for the enum
      conf.in_mode = (st & TIMER_LSB_MSB) >> 4; 
      break;

    case tsf_mode:
      /* Display the counting mode, only */

      // Get the couting mode bits (3,2,1), first shifting them to the right
      conf.count_mode = (uint8_t)((st >> 1) & 0x7); 

      // Special cases
      // 111* -> 3
      // 110* -> 2

      if (conf.count_mode == 7){
        conf.count_mode = 3;
      } else if (conf.count_mode == 6){
        conf.count_mode = 2;
      }
      break;

    case tsf_base:
      /* Display the counting base, only */
      // See if it's in BCD
      conf.bcd = (st & TIMER_BCD);
      break;

    default:
      printf("Unknown field\n");
      return 1;
  }

  return timer_print_config(timer, field, conf);
}

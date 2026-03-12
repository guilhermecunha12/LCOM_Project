#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t target_port = TIMER_0 + timer; // base port 0x40 + the timer selected
  uint8_t rb_cmd = 0xE0  | TIMER_RB_SEL(timer); // build of the read back command to retreive a timer's config (avoid overwrite of 4 LSb)
  
  if(sys_outb(TIMER_CTRL,rb_cmd)!=0) return -1;
  
  uint8_t status_byte;
  util_sys_inb(target_port,&status_byte); // read status byte
  uint8_t control_byte =  (timer << 6) | TIMER_LSB_MSB | (status_byte & 0x0F); // build control byte to configure our timer

  if(sys_outb(TIMER_CTRL,control_byte)) return -1; // write control_byte to control_register

  uint16_t divider = TIMER_FREQ / (uint16_t) freq;
  uint8_t lsb, msb; 
  // Write in the specified order defined in the control byte (LSB followed by MSB)
  util_get_LSB(divider,&lsb);
  util_get_MSB(divider,&msb);
  if(sys_outb(target_port,lsb)!=0 || sys_outb(target_port,msb)!=0) return -1;
 
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
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

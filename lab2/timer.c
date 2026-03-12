#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
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
      enum timer_init mode;
      int init = (st & TIMER_LSB_MSB) >> 4;
      conf.in_mode = init;
      break;

    case tsf_mode:
      /* Display the counting mode, only */
      uint8_t countingMode = (st & 0x0E);
      conf.in_mode = countingMode;
      break;

    case tsf_base:
      /* Display the counting base, only */
      conf.bcd = (st & 0x01) ? true : false;
      break;

    default:
      printf("Unkown field\n");
      return 1;
  }
  
  timer_print_config(timer, field, conf);

  return 0;
}
union timer_status_field_val {
    uint8_t byte;               /* The status byte */
    enum timer_init in_mode;    /* The initialization mode */
    uint8_t count_mode;         /* The counting mode: 0, 1,.., 5 */
    bool bcd;                   /* The counting base, true if BCD */
};
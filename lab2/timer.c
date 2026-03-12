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
  // Timer: especifica o timer cuja configuração deve ser lida (0, 1 ou 2)
  // st: address onde o status byte deve ser guardado
  // Construir o comando readback correto
  uint8_t read_back_command = 0;
  read_back_command |= TIMER_RB_CMD; // Sinalizar que iremos fazer um read-back command
  // Colocamos bit do counter value a 1 porque queremos ler a 0 o status bit (Read programmed mode - enabled when low : 0)
  read_back_command |= TIMER_RB_COUNT_;
  read_back_command |= TIMER_RB_SEL(timer); // Permite selecionar o counter do timer especificado
  // Escrever no control register
  sys_outb(TIMER_CTRL, read_back_command);
  // Ler status byte do port correto e colocar no endereço onde vamos guardar o status byte
  int port = 0x40 + timer;
  util_sys_inb(port, st);
  return 0;
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
      int init = (st & TIMER_LSB_MSB) >> 4; // convert the init mode to int;
      conf.in_mode = init;
      break;

    case tsf_mode:
      /* Display the counting mode, only */
      uint8_t countingMode = (st & 0x0E); //get the couting mode, by applying the mask
      conf.in_mode = countingMode;
      break;

    case tsf_base:
      /* Display the counting base, only */
      conf.bcd = (st & TIMER_BCD) ? true : false; //see if it's in BCD
      break;

    default:
      printf("Unkown field\n");
      return 1;
  }
  
  timer_print_config(timer, field, conf);

  return 0;
}
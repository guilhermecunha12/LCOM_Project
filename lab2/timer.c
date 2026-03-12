#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

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
      conf.in_mode = (st >> 1) & 0x7;
      break;

    case tsf_mode:
      /* Display the counting mode, only */
      conf.count_mode= (uint8_t) (st & 0xE);  //get the couting mode, by applying the mask
      break;

    case tsf_base:
      /* Display the counting base, only */
      conf.bcd = (st & TIMER_BCD); //see if it's in BCD
      break;

    default:
      printf("Unkown field\n");
      return 1;
  }
  
  timer_print_config(timer, field, conf);

  return 0;
}

#include "kbc.h"
#include <lcom/lcf.h>


int kbd_hook_id;
int (kbd_subscribe_int) (uint8_t *bit_no){
  kbd_hook_id = *bit_no;
  if(sys_irqsetpolicy(KBD_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&kbd_hook_id)) return 1;
  *bit_no = BIT(*bit_no);
  return 0;
}

int (kbd_unsubscribe_int)(){
  return sys_irqrmpolicy(&kbd_hook_id) ? 1 : 0;
}

int read_scancode(uint8_t *scancode){
  int n = N_TRIES;
  uint8_t status_byte;
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_OBF,&status_byte)) return 1;  // read the status byte from the output buffer
    if(status_byte & KBC_OBF){ // if the output buffer is full (we can read the scancode)
      if(util_sys_inb(KBC_OB,scancode)) return 1; 
      return (status_byte & KBC_ERROR) ? 1 : 0; // if there was an error (signaled by 2 MSB parity and timeout return 1 else 0)
    } 
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)

  }
  return 1;
}

void (kbc_ih) () {

}
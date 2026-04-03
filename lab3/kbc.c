#include "i8042.h"
#include "kbc.h"
#include <lcom/lcf.h>

static uint8_t scancode;
int kbd_hook_id;

// Enum with 


int (kbd_subscribe_int) (uint8_t *bit_no){
  kbd_hook_id = *bit_no;
  if(sys_irqsetpolicy(KBD_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&kbd_hook_id)) return 1;
  *bit_no = BIT(*bit_no);
  return 0;
}

int (kbd_unsubscribe_int)(){
  return sys_irqrmpolicy(&kbd_hook_id) ? 1 : 0;
}

int read_scancode(uint8_t *byte){
  int n = N_TRIES;
  uint8_t status_byte;
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_STATUS_REG,&status_byte)) return 1;  // read the status byte from the status register
    if(status_byte & KBC_OBF){ // if the output buffer is full (we can read the scancode)
      if(util_sys_inb(KBC_OB,byte)) return 1; 
      return (status_byte & KBC_ERROR) ? 1 : 0; // if there was an error (signaled by 2 MSB parity and timeout return 1 else 0)
    } 
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)
  }
  return 1;
}

void (kbc_ih) () {
    uint8_t byte;
    if(read_scancode(&byte) == 0) scancode=byte;
}


// Instead of using extern, using getters and setters to access scancode elsewhere (lab report)

uint8_t get_scancode(){
  return scancode;
}

void set_scancode(uint8_t byte){
   scancode = byte;
}

// Generic function to write a command byte to a port
int write_KBC_command(uint8_t port, uint8_t command_byte){
  int n = N_TRIES;
  uint8_t status_byte;
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_STATUS_REG,&status_byte)) return 1;  // read the status byte from the status register
    if(!(status_byte & KBC_IBF)){ // if the input buffer is empty - 0 - (we can issue command)
      if(sys_outb(port, command_byte)) return 1;
      return 0;
    } 
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)
  }
  return 1;
}

// Generic function to read an output value from a port
int read_KBC_output_buf(uint8_t port, uint8_t* value){
  int n = N_TRIES;
  uint8_t status_byte;
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_STATUS_REG,&status_byte)) return 1;  // read the status byte from the status register
    if(status_byte & KBC_OBF){ // if the output buffer is full (we can read the scancode)
      if(util_sys_inb(KBC_OB,value)) return 1;
      // Discard values if needed
      if(status_byte & KBC_ERROR) return 1;
      if(status_byte & KBC_MOUSE_DATA) return 1;
    } 
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)
  }
  return 1;
}

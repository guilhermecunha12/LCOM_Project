#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

static uint8_t scancode;
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

// only for readability
int read_scancode(uint8_t *byte){
  return read_KBC_output_buf(byte, false) ? 1 : 0;
}

// only modifies scancode variable if it was possible to correctly read a scancode
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

int write_KBC_command(uint8_t port, uint8_t command_byte){
  int n = N_TRIES;
  uint8_t status_byte;
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_STATUS_REG,&status_byte)) return 1;  // read the status byte from the status register
    if(!(status_byte & KBC_IBF)){ // if the input buffer is empty - 0 - (we can issue command)
      return sys_outb(port, command_byte) ? 1 : 0;
    } 
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)
  }
  return 1;
}

int read_KBC_output_buf(uint8_t* value, bool mouse_related_data){
  int n = N_TRIES;
  uint8_t status_byte;
  
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_STATUS_REG,&status_byte)) { // read the status byte from the status register
      printf("Error while reading status byte.");
      return 1;  
    }
    if(status_byte & KBC_OBF){ // if the output buffer is full (we can read the scancode)
      if(util_sys_inb(KBC_OB,value)) {
        printf("Error while reading output buffer inside read_KBC.");
        return 1;
      }
      // Discard values if needed
      if(status_byte & KBC_ERROR) {
        printf("Status byte indicates error.");
        return 1;
      }
      // In case of wanting to read mouse data
      if(mouse_related_data && !(status_byte & KBC_MOUSE_DATA)){
        // If the desired data to be read is mouse related, when the bit is set, the value will be considered value for mouse. If bit not set, data is discarded
        printf("Mouse related data expected but not from mouse.");
        return 1;
      }
      if(!mouse_related_data && (status_byte & KBC_MOUSE_DATA)){
        printf("Not mouse related data expected but received from mouse.");
        return 1;
      }
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)
  }
  printf("HHHASDKHASDOIHSAODIH.");
  return 1;
}

int reset_interrupts(){
  // Restore interrupts
  uint8_t command_byte;
  // Write the read command byte to command register
  if(write_KBC_command(KBC_CMD_REG, READ_COMMAND_BYTE)) return 1;
  // Read the command byte from the output buffer
  if(read_KBC_output_buf(&command_byte, false)) return 1;
  // Activate keyboard interrupts
  command_byte |= ENABLE_KEYBOARD_INTERRUPTS;
  // Issue the write command byte to the command register
  if(write_KBC_command(KBC_CMD_REG, WRITE_COMMAND_BYTE)) return 1;
  // Place the new command byte value in the input buffer
  if(write_KBC_command(KBC_IB, command_byte)) return 1;
  return 0;
}


int disable_mouse_interrupts(){
  // Disable interrupts
  uint8_t command_byte;
  // Write the read command byte to command register
  if(write_KBC_command(KBC_CMD_REG, READ_COMMAND_BYTE)) return 1;
  // Read the command byte from the output buffer
  if(read_KBC_output_buf(&command_byte, false)) return 1;
  // Deactivate keyboard interrupts
  command_byte &= ~ENABLE_MOUSE_INTERRUPTS;
  // Issue the write command byte to the command register
  if(write_KBC_command(KBC_CMD_REG, WRITE_COMMAND_BYTE)) return 1;
  // Place the new command byte value in the input buffer
  if(write_KBC_command(KBC_IB, command_byte)) return 1;
  return 0;
}

int enable_mouse_interrupts(){
  // Restore interrupts
  uint8_t command_byte;
  // Write the read command byte to command register
  if(write_KBC_command(KBC_CMD_REG, READ_COMMAND_BYTE)) return 1;
  // Read the command byte from the output buffer
  if(read_KBC_output_buf(&command_byte, false)) return 1;
  // Activate keyboard interrupts
  command_byte |= ENABLE_MOUSE_INTERRUPTS;
  // Issue the write command byte to the command register
  if(write_KBC_command(KBC_CMD_REG, WRITE_COMMAND_BYTE)) return 1;
  // Place the new command byte value in the input buffer
  if(write_KBC_command(KBC_IB, command_byte)) return 1;
  return 0;
}

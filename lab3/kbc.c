#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

static uint8_t scancode[2]; 
static uint8_t last_byte_read;
static bool second_byte = false; // flag for the 2 byte scancode
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
  return read_KBC_output_buf(byte, 0) ? 1 : 0;
}

// only modifies scancode variable if it was possible to correctly read a scancode
void (kbc_ih) () {
  uint8_t byte;
  if(read_scancode(&byte) == 0) last_byte_read=byte;
}

uint8_t* get_scancode(){
  return scancode;
}
// Instead of using extern, using getters and setters to access scancode elsewhere (lab report)

uint8_t get_last_byte_read(){
  return last_byte_read;
}

void set_last_byte_read(uint8_t byte){
  last_byte_read = byte;
}

uint8_t is_make_code(uint8_t scancode[2]){
  return !(MSB(scancode[1]));
}

// port == 0x64 -> KBC command
// port == 0x60 -> KBC command argument
int write_KBC_command(uint8_t port, uint8_t command_byte){
  int n = N_TRIES;
  uint8_t status_byte;
  while(n--){ // we should wait long enough after some retries
    if(util_sys_inb(KBC_STATUS_REG, &status_byte)) return 1;  // read the status byte from the status register
    if(!(status_byte & KBC_IBF)){ // if the input buffer is empty - 0 - (we can issue command)
      return sys_outb(port, command_byte) ? 1 : 0;
    } 
    tickdelay(micros_to_ticks(DELAY_US)); // wait up until 20ms (as described in lab report)
  }
  return 1;
}

int read_KBC_output_buf(uint8_t* value, bool mouse_data){
  uint8_t status_byte;
  if(util_sys_inb(KBC_STATUS_REG, &status_byte)) return 1;  // read the status byte from the status register
  if(status_byte & KBC_OBF){ // if the output buffer is full (we can read the scancode)
    if(util_sys_inb(KBC_OB, value)) return 1;
    // Discard values if needed
    if(status_byte & KBC_ERROR) return 1;
    // In case of wanting to read mouse data
    if(mouse_data && !(status_byte & KBC_MOUSE_DATA)) return 1;
    if(!mouse_data && (status_byte & KBC_MOUSE_DATA)) return 1;
    return 0;
  }
  return 1;
}

int reset_interrupts(){
  // Restore interrupts
  uint8_t command_byte;
  // Write the read command byte to command register
  if(write_KBC_command(KBC_CMD_REG, READ_COMMAND_BYTE)) return 1;
  // Read the command byte from the output buffer
  if(read_KBC_output_buf(&command_byte, 0)) return 1;
  // Activate keyboard interrupts
  command_byte |= ENABLE_KEYBOARD_INTERRUPTS;
  // Issue the write command byte to the command register
  if(write_KBC_command(KBC_CMD_REG, WRITE_COMMAND_BYTE)) return 1;
  // Place the new command byte value in the input buffer
  if(write_KBC_command(KBC_IB, command_byte)) return 1;
  return 0;
}

bool process_scancode() {
  kbc_ih(); // Call interrupt handler
  // if MSB of the scancode == 0, it's a makecode; else if MSB == 1, it's a breakcode
  last_byte_read = get_last_byte_read();
  if (second_byte) { // we are reading the second byte of the scancode
    scancode[0] = TWO_BYTE_PREFIX;
    scancode[1] = last_byte_read; // 2-bytes read
    second_byte = false; // reset the flag
    return true;

  } else { // not reading the second byte of a scancode

    if (last_byte_read == TWO_BYTE_PREFIX) { // if this is true, the scancode we are reading has 2 bytes
      second_byte = true; // in the next IRQ 1 line raise, the second byte of the scancode will be read
      // do nothing more, only print in the next iteration (IRQ 1 line raise)
      return false; // Not ready to print yet, need to wait for the second byte to be read
    } else {
      scancode[0] = 0;
      scancode[1] = last_byte_read;
      second_byte = false;
      return true;
    }
  }
}



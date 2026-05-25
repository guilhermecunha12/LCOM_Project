#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"
/**
 * @brief Array to store the scancode bytes read from the KBC output buffer.
 * @details Has two bytes to accommodate both single-byte and two-byte scancodes. Conventions: if it's a single-byte scancode, scancode[0] will be 0 and scancode[1] will hold the byte read; if it's a two-byte scancode, scancode[0] will hold the prefix (0xE0) and scancode[1] will hold the second byte read.
 */
static uint8_t scancode[2]; 

/**
 * @brief Stores the last scancode byte read from the KBC output buffer.
 * @details Updated by the keyboard interrupt handler.
 */
static uint8_t last_byte_read;


/**
 * @brief This variable is used to indicate whether we are reading the second byte of a scancode.
 * @details Set to true when the first byte of a two-byte scancode is received, being updated inside the process_scancode() function. Reset to false after the second byte is read or if a single-byte scancode is read.
 */
static bool second_byte = false;

/**
 * @brief This variable is used to store the hook ID for the keyboard interrupt.
 * @details Used for subscribing and unsubscribing keyboard interrupts. Initialized in kbd_subscribe_int() and used in kbd_unsubscribe_int().
 */
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


int read_scancode(uint8_t *byte){
  return read_KBC_output_buf(byte, 0) ? 1 : 0;
}


void (kbc_ih) () {
  uint8_t byte;
  if(read_scancode(&byte) == 0) last_byte_read=byte;
}

uint8_t* get_scancode(){
  return scancode;
}


uint8_t get_last_byte_read(){
  return last_byte_read;
}


uint8_t is_make_code(uint8_t scancode[2]){
  return !(MSB(scancode[1]));
}


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
    if(mouse_data && !(status_byte & KBC_MOUSE_DATA)) return 1; // if we want to read mouse data but the mouse data bit is not set, discard the value read from the output buffer
    if(!mouse_data && (status_byte & KBC_MOUSE_DATA)) return 1; // if we want to read keyboard data but the mouse data bit is set, discard the value read from the output buffer
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
  kbc_ih();
  last_byte_read = get_last_byte_read();
  if (second_byte) {
    scancode[0] = TWO_BYTE_PREFIX;
    scancode[1] = last_byte_read;
    second_byte = false; // reset the flag
    return true;

  } else {

    if (last_byte_read == TWO_BYTE_PREFIX) {
      second_byte = true;
      return false; // Not ready to print yet, need to wait for the second byte to be read
    } else {
      // A single byte scancode was completely read
      scancode[0] = 0;
      scancode[1] = last_byte_read;
      second_byte = false;
      return true;
    }
  }
}



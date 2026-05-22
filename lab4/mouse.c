#include <lcom/lcf.h>
#include "../lab3/i8042.h"
#include "../lab3/kbc.h"
#include "mouse.h"
#include "i8042_mouse.h"

/**
 * @brief Index to track which byte of the mouse packet is being read.
 * @details Ranges from 0 to 2, indicating the first, second, or third byte of the packet.
 * Resets to 0 after a complete packet is parsed.
 */
static int byte_index = 0;

/**
 * @brief Sign bit for the x-coordinate delta value.
 * @details Extracted from bit 4 of the first packet byte. Used to determine if delta_x is negative (2's complement).
 */
static bool x_sign_bit = 0;

/**
 * @brief Sign bit for the y-coordinate delta value.
 * @details Extracted from bit 5 of the first packet byte. Used to determine if delta_y is negative (2's complement).
 */
static bool y_sign_bit = 0;

/**
 * @brief The current mouse packet being assembled.
 * @details Populated incrementally as bytes are received from interrupts. Complete when all 3 bytes have been read.
 */
static struct packet pp;

/**
 * @brief The most recent byte read from the mouse.
 * @details Updated by the mouse interrupt handler. Used for packet population.
 */
static uint8_t mouse_byte;

/**
 * @brief The interrupt hook ID for the mouse.
 * @details Used for subscribing and unsubscribing mouse interrupts. Initially defined in mouse_subscribe_int() and used in mouse_unsubscribe_int().
 */
int mouse_hook_id;

int mouse_subscribe_int(uint8_t* bit_no){
  mouse_hook_id = *bit_no;
  if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id)) return 1;
  *bit_no = BIT(*bit_no);
  return 0;
}

int mouse_unsubscribe_int(){
  return sys_irqrmpolicy(&mouse_hook_id) ? 1 : 0;
}

struct packet get_mouse_packet() {
  return pp;
}

int send_to_mouse(uint8_t cmd){
  uint8_t response;
  uint8_t n = N_TRIES;
  // Do while so we can check response and retry if we don't get an ACK by N_tries
  while(n--) {
    // Before sending any command to the mouse, data reporting must be disabled to prevent interference from packets sent by the mouse (lab guide)
    if(cmd != ENABLE_DATA_REPORTING && cmd != DISABLE_DATA_REPORTING){
      disable_mouse_data_reporting();
    }
    // write_kbc_command already waits for input buffer being empty
    // Request forwarding of command byte to the mouse
    if(write_KBC_command(KBC_CMD_REG, WRITE_BYTE_TO_MOUSE_CMD)) return 1;
    if(write_KBC_command(KBC_IB,cmd)) return 1; // mouse command - argument of the previous command (no support for situations where multiple arguments are needed)

    // Reenable data reporting
    if(cmd != ENABLE_DATA_REPORTING && cmd != DISABLE_DATA_REPORTING){
      enable_mouse_data_reporting();
    }
    
    if (util_sys_inb(KBC_OB, &response)) return 1; // read the response byte from the output buffer of the KBC

    /* Although recommended, this approach does not work

    // Wait a bit to wait for the status byte of the KBC to be updated (to set the output buffer bit to 1)
    tickdelay(micros_to_ticks(DELAY_US));

    if(read_KBC_output_buf(&response, 1)) return 1;
    
    */

    if(response==ACK) return 0;
  }
  return 1;
}

int enable_mouse_data_reporting(){
  return send_to_mouse(ENABLE_DATA_REPORTING);
} 

int disable_mouse_data_reporting(){
  return send_to_mouse(DISABLE_DATA_REPORTING);
}


void (mouse_ih) () {
  if(read_KBC_output_buf(&mouse_byte, 1)) return;
}

int16_t get_delta(bool sign_bit, uint8_t mouse_byte) {
  int16_t delta = 0; // will be a 9-bit 2's complement integer
  
  if (sign_bit) delta |= 0xFF00; // sign extend if sign_bit == 1
  delta |= mouse_byte; // LSByte of delta will now be equal to mouse_byte

  return delta;
}

void parse_first_byte(struct packet* pp, bool* x_sign_bit, bool* y_sign_bit, uint8_t mouse_byte) {
  pp->lb = (mouse_byte & BIT(0)) != 0;
  pp->rb = (mouse_byte & BIT(1)) != 0;
  pp->mb = (mouse_byte & BIT(2)) != 0;
  *x_sign_bit = (mouse_byte & BIT(4)) != 0;
  *y_sign_bit = (mouse_byte & BIT(5)) != 0;
  pp->x_ov = (mouse_byte & BIT(6)) != 0;
  pp->y_ov = (mouse_byte & BIT(7)) != 0;
}

bool is_mouse_click() {
  return pp.lb;
}

bool is_mouse_move() {
  return pp.delta_x != 0 || pp.delta_y != 0;
}


bool process_packet() {
  mouse_ih(); // note: if there is a read failure here, the old value of mouse_byte will be treated as the new packet byte in the next line (maybe add a static variable that would indicate an error, like if it was a return value)

  if (byte_index == 0 && (mouse_byte & BIT(3))) { // the 3rd bit of the first packet byte is always 1
    pp.bytes[0] = mouse_byte;

    // populate pp struct and sign bits variables
    parse_first_byte(&pp, &x_sign_bit, &y_sign_bit, mouse_byte);

    byte_index++; // next interrupt byte index

  } else if (byte_index == 1) {
    pp.bytes[1] = mouse_byte;
    pp.delta_x = get_delta(x_sign_bit, mouse_byte);

    byte_index++; // next byte index

  } else if (byte_index == 2) {
    pp.bytes[2] = mouse_byte;
    pp.delta_y = get_delta(y_sign_bit, mouse_byte);
  
    byte_index = 0; // reset byte_index

    return true; // packet is ready
  }

  return false;
}

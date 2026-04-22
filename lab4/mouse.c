#include <lcom/lcf.h>
#include "../lab3/i8042.h"
#include "../lab3/kbc.h"
#include "mouse.h"
#include "i8042_mouse.h"

static uint8_t mouse_byte; // static variable that could be accessed anywhere in the file
int mouse_hook_id;

// IMPORTANT: bit_no can never be >= 8, otherwise, an overflow will happen in setting the bit mask
int mouse_subscribe_int(uint8_t* bit_no){
  mouse_hook_id = *bit_no;
  if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id)) return 1;
  *bit_no = BIT(*bit_no);
  return 0;
}

int mouse_unsubscribe_int(){
  return sys_irqrmpolicy(&mouse_hook_id) ? 1 : 0;
}

// Also need to implement subscribe and unsubscribe for the keyboard

void set_mouse_byte(uint8_t data){
  mouse_byte = data;
}

uint8_t get_mouse_byte(){
  return mouse_byte;
}


// Generic function to send a command directly into the mouse
int send_to_mouse(uint8_t cmd){
  uint8_t response;
  uint8_t n=N_TRIES;

  // Do while so we can check response and retry if we don't get an ACK by N_tries
  while(n--) {

    // disable data reporting before sending any other command to the mouse
    if(cmd != ENABLE_DATA_REPORTING && cmd != DISABLE_DATA_REPORTING){
      printf("disabling mouse reports...\n");
      disable_mouse_data_reporting();
    }

    // write_kbc_command already waits for input buffer being empty
    // Request forwarding of command byte to the mouse
    if(write_KBC_command(KBC_CMD_REG, WRITE_BYTE_TO_MOUSE_CMD)) {
      printf("Error while writing command to the KBC Command Register.\n");
      return 1;
    } 
    
    if(write_KBC_command(KBC_IB, cmd)) {
      printf("Error while writing command to the KBC Input Buffer.\n");
      return 1;
    } 

    // reenable data reporting after sending the command to the mouse
    if(cmd != ENABLE_DATA_REPORTING && cmd != DISABLE_DATA_REPORTING){
      printf("reenabling mouse reports...\n");
      enable_mouse_data_reporting();
    }
    
    // Reads output buffer after checking for errors and waiting for it being full
    if(read_KBC_output_buf(&response, true)) {
      continue;
    }

    if(response == ACK) {
      printf("Received acknowledgement byte.\n");
      return 0;
    }
  } 
  printf("Could not send command to the mouse (exceeded retries).\n");
  return 1;
} 

//Enable data reporting with command 0xF4

int enable_mouse_data_reporting(){
  return send_to_mouse(ENABLE_DATA_REPORTING);
} 

int disable_mouse_data_reporting(){
  return send_to_mouse(DISABLE_DATA_REPORTING);
}


// The function will be responsible by reading the byte from the buffer and then updating 
void (mouse_ih) () {
  uint8_t mouse_data;
  if(read_KBC_output_buf(&mouse_data, true)) return;
  set_mouse_byte(mouse_data);
}


int16_t get_delta(bool sign_bit, uint8_t mouse_byte) {
  int16_t delta = 0; // will be a 9-bit 2's complement integer
  
  if (sign_bit) delta |= 0xFF00; // sign extend if sign_bit == 1
  delta |= mouse_byte; // LSByte of x_movement will now be equal to mouse_byte

  return delta;
}

void parse_first_byte(struct packet* pp, bool* x_sign_bit, bool* y_sign_bit, uint8_t mouse_byte) {

  // Assigning results of conditions because all fields are bool types

  pp->lb = (mouse_byte & BIT(0)) != 0;
  pp->rb = (mouse_byte & BIT(1)) != 0;
  pp->mb = (mouse_byte & BIT(2)) != 0;
  *x_sign_bit = (mouse_byte & BIT(4)) != 0;
  *y_sign_bit = (mouse_byte & BIT(5)) != 0;
  pp->x_ov = (mouse_byte & BIT(6)) != 0;
  pp->y_ov = (mouse_byte & BIT(7)) != 0;
}


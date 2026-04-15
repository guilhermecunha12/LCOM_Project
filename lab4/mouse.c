#include <lcom/lcf.h>
#include "lab3/i8042.h"
#include "lab3/kbc.h"
#include "mouse.h"
#include "i8042_mouse.h"

static uint8_t mouse_byte; // static variable that could be accessed anywhere in the file
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
    // write_kbc_command already waits for input buffer being empty
    // Request forwarding of command byte to the mouse
    if(write_KBC_command(0x64,0xD4)) return 1;
    if(write_KBC_command(0x60,cmd)) return 1;
    // Reads output buffer after checking for errors and waiting for it being full
    if(read_KBC_output_buf(&response,true)) return 1;
    if(response==ACK) return 0;
  } 
  
  return 1;
} 

//Enable data reporting with command 0xF4

int mouse_enable_data_reporting(){
  return send_to_mouse(ENABLE_DATA_REPORTING);
} 

int mouse_disable_data_reporting(){
  return send_to_mouse(DISABLE_DATA_REPORTING);
}




// The function will be responsible by reading the byte from the buffer and then updating 
void (mouse_ih) () {
  uint8_t mouse_data;
  if(read_KBC_output_buf(&mouse_data, true)) return;
  set_mouse_byte(mouse_data);
}
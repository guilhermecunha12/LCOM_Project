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

// The function will be responsible by reading the byte from the buffer and then updating 
void (mouse_ih) () {
  uint8_t mouse_data;
  if(read_KBC_output_buf(&mouse_data, true)) return;
  set_mouse_byte(mouse_data);
}


// Utility functions
void sign_extend(int16_t* num) {
  *num << 7;
  *num >> 7; // arithmetic right shift
}

int16_t get_delta(int sign_bit, uint8_t mouse_byte) {
    int16_t delta = 0; // will be a 9-bit 2's complement integer
    
    if (sign_bit) delta |= BIT(9);
    delta |= mouse_byte; // LSByte of x_movement will now be equal to mouse_byte
    sign_extend(delta); // to make it interpretable in 2's complement

    return delta;
}

void parse_first_byte(struct packet* pp, int* x_sign_bit, int* y_sign_bit, uint8_t mouse_byte) {
    pp->lb = mouse_byte & BIT(1);
    pp->rb = mouse_byte & BIT(2);
    pp->mb = mouse_byte & BIT(3);
    x_sign_bit = mouse_byte & BIT(4);
    y_sign_bit = mouse_byte & BIT(5);
    pp->x_ov = mouse_byte & BIT(6);
    pp->y_ov = mouse_byte & BIT(7);
}
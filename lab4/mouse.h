#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>

// subscribe and unsubscribe mouse interrupts 
int mouse_subscribe_int(uint8_t* bit_no);
int mouse_unsubscribe_int();

// Setter for mouse data
void set_mouse_byte(uint8_t data);
// Getter for mouse data
uint8_t get_mouse_byte();
// Mouse interrupt handler
void (mouse_ih) ();

#endif
#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include "i8042_mouse.h"

// Setter for mouse data
void set_mouse_byte(uint8_t data);
// Getter for mouse data
uint8_t get_mouse_byte();
// Mouse interrupt handler
void (mouse_ih) ();

// Functions to enable/disable data packets being sent on the go

int send_to_mouse(uint8_t cmd);
int mouse_enable_data_reporting(); 
int mouse_disable_data_reporting(); 

#endif
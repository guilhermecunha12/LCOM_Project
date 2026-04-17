#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include "i8042_mouse.h"

// subscribe and unsubscribe mouse interrupts 
int mouse_subscribe_int(uint8_t* bit_no);
int mouse_unsubscribe_int();

// Setter for mouse data
void set_mouse_byte(uint8_t data);
// Getter for mouse data
uint8_t get_mouse_byte();
// Mouse interrupt handler
void (mouse_ih) ();

// Functions to enable/disable data packets being sent on the go

int send_to_mouse(uint8_t cmd);
int enable_mouse_data_reporting(); 
int disable_mouse_data_reporting(); 


// Computes a coordinate's delta (x or y) of the mouse's movement in a 16-bit sign-extended integer.
int16_t get_delta(bool sign_bit, uint8_t mouse_byte);
// Parses the first byte of a data packet received by the mouse and populates a packet struct and sign bits variables.
void parse_first_byte(struct packet* pp, bool* x_sign_bit, bool* y_sign_bit, uint8_t mouse_byte);

#endif

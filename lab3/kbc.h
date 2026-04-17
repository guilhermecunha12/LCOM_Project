#ifndef KBC_H
#define KBC_H

#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

void (kbc_ih) ();
int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int();
uint8_t (get_scancode) ();
void set_scancode(uint8_t byte);

// Generic function to write a command byte to a port
int write_KBC_command(uint8_t port, uint8_t command_byte);

// Decided to update function used in lab3 to not implement similar function two times (both in kbc.c and mouse.c)
// Generic function to read data from the output buffer.
// If mouse_related is true, the available data at the buffer should be interpreted as a mouse data
// If mouse_related is false, the available data at the buffer should be interpreted as KBC data
int read_KBC_output_buf(uint8_t* value, bool mouse_related);
int reset_interrupts();
int disable_mouse_interrupts();
int enable_mouse_interrupts();

#endif

#ifndef KBC_H
#define KBC_H

#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

void (kbc_ih) ();
int kbd_subscribe_int(uint8_t* bit_no);
int kbd_unsubscribe_int();
uint8_t (get_scancode) ();
void set_scancode(uint8_t byte);

// Generic function to write a command byte to a port
int write_KBC_command(uint8_t port, uint8_t command_byte);

// Function that allows reads from the output buffer
int read_KBC_output_buf(uint8_t* value, bool mouse_related_data);
int reset_interrupts();

#endif

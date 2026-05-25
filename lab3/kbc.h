#ifndef KBC_H
#define KBC_H

#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

void (kbc_ih) ();
int kbd_subscribe_int(uint8_t* bit_no);
int kbd_unsubscribe_int();

uint8_t* get_scancode();

uint8_t get_last_byte_read();
void set_last_byte_read(uint8_t byte);

uint8_t is_make_code(uint8_t scancode[2]);
void set_make_code(uint8_t make);

// Generic function to write a command byte to a port
int write_KBC_command(uint8_t port, uint8_t command_byte);

// Function that allows reads from the output buffer
int read_KBC_output_buf(uint8_t* value, bool mouse_related_data);
int reset_interrupts();

// New functions defined for the project
bool process_scancode();


#endif

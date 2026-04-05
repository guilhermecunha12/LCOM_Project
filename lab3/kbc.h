#ifndef KBC_H
#define KBC_H

#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

//SCANCODES
#define ESC_BREAKCODE 0x81 // breakcode of the ESC key
#define TWO_BYTE_PREFIX 0xE0 // prefix of 2-byte long scancodes. Needed to know if the current scancode has 1 or 2 bytes (3 bytes not supported - lab guides). This is the only valid 2-byte scancode prefix considered.
#define MSB(n) (n >> 7) // MSB of a byte

void (kbc_ih) ();
int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int();

uint8_t (get_scancode) ();
void set_scancode(uint8_t byte);

int write_KBC_command(uint8_t port, uint8_t command_byte);

int read_KBC_output_buf(uint8_t port, uint8_t* value);

int reset_interrupts();

#endif

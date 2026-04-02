#ifndef KBC_H
#define KBC_H

#include <stdint.h>
#include <stdio.h>

// Keyboard must respond to a command within 20ms
#define DELAY_US 20000 
// Keyboard Interrupt Line 
#define KBD_IRQ 1
#define KBC_OB 0x60 // kbc output buffer 
#define KBC_IB 0x60 // kbc input buffer
#define KBC_STATUS_REG 0x64 // kbc status register
#define KBC_CMD_REG 0x64 // kbc command register

// MASKS FOR STATUS BYTE
#define KBC_OBF BIT(0)
#define KBC_IBF BIT(1)
#define KBC_ERROR (BIT(6) | BIT(7))

// ATTEMPT NUMBER
#define N_TRIES 10 // number of tries to read from the kbc

//SCANCODES
#define ESC_BREAKCODE 0x81 // breakcode of the ESC key
#define TWO_BYTE_PREFIX 0xE0 // prefix of 2-byte long scancodes. Needed to know if the current scancode has 1 or 2 bytes (3 bytes not supported - lab guides). This is the only valid 2-byte scancode prefix considered.
#define MSB(n) (n >> 7) // MSB of a byte

void (kbc_ih) ();
int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int();

uint8_t (get_scancode) ();
void set_scancode(uint8_t byte);


#endif

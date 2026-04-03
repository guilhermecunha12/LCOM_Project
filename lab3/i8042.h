#ifndef I8042_H
#define I8042_H

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
#define KBC_MOUSE_DATA BIT(5)

// ATTEMPT NUMBER
#define N_TRIES 10 // number of tries to read from the kbc

// Command byte fields
#define DISABLE_MOUSE_INTERFACE BIT(5)
#define DISABLE_KEYBOARD_INTERFACE BIT(4)
#define ENABLE_MOUSE_INTERRUPTS BIT(1)
#define ENABLE_KEYBOARD_INTERRUPTS BIT(0)

// Available commands
#define READ_COMMAND_BYTE 0x20
#define WRITE_COMMAND_BYTE 0x60

// Key related macros
#define ESC_BREAKCODE 0x81
#define BREAKCODE BIT(7)
#define TWO_BYTE_LONG 0xE0

#endif

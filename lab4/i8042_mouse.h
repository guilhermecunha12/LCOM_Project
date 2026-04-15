#ifndef I8042_MOUSE_H
#define I8042_MOUSE_H

// Mouse interrupt line
#define MOUSE_IRQ 12
#define TIMER0_IRQ 0


#define WRITE_BYTE_TO_MOUSE_CMD 0xD4 // Write Byte to Mouse Command
#define ENABLE_DATA_REPORTING 0xF4 // Enable Mouse Data Reporting Command (stream mode only)
#define DISABLE_DATA_REPORTING 0xF5

// Responses are not immediate when communicating between the KBC and mouse so we must add a timeout + retries
#define N_TRIES 10 
#define DELAY_US 2000 

#define ACK 0xFA
#define NACK 0xFE

#endif
#ifndef I8042_MOUSE_H
#define I8042_MOUSE_H

// Mouse interrupt line
#define MOUSE_IRQ 12


#define WRITE_BYTE_TO_MOUSE_CMD 0xD4 // Write Byte to Mouse Command
#define ENABLE_DATA_REPORTING 0xF4 // Enable Mouse Data Reporting Command (stream mode only)
#define DISABLE_DATA_REPORTING 0xF5

#define ACK 0xFA
#define NACK 0xFE

#endif


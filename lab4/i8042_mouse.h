#ifndef I8042_MOUSE_H
#define I8042_MOUSE_H

/**
 * @brief Mouse interrupt request line number.
 */
#define MOUSE_IRQ 12

/**
 * @brief Command to write a byte to the mouse via the KBC.
 */
#define WRITE_BYTE_TO_MOUSE_CMD 0xD4

/**
 * @brief Enable Mouse Data Reporting Command (stream mode only)
 */
#define ENABLE_DATA_REPORTING 0xF4

/**
 * @brief Disable Mouse Data Reporting Command (stream mode only)
 */
#define DISABLE_DATA_REPORTING 0xF5

/**
 * @brief Acknowledgment byte response from the mouse, after sending a byte to it.
 */
#define ACK 0xFA

/**
 * @brief Byte response from the mouse after sending a byte to it, that signals an error.
 */
#define NACK 0xFE

#endif

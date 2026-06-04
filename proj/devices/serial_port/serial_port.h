#include <lcom/lcf.h>
#include "../subscribe.h"

/**
 * @brief This is used as a numerator to set the bit-rate (number of bits trasmitted per second) of the serial port (clock frequency divided by 16).
 */
#define DIVIDED_CLOCK_FREQUENCY 115200


/**
 * @brief The base address of COM1 serial port registers.
 */
#define COM1_BASE 0x3F8

/** 
 * @brief The offset of the Interrupt Enable Register (IER) from the base address of a UART serial port.
*/
#define IER_OFFSET 1

#define IER_RECEIVED_DATA_AVAILABLE_INTERRUPT BIT(0)
#define IER_TRANSMITTER_HOLDING_REGISTER_EMPTY_INTERRUPT BIT(1)
#define IER_LINE_STATUS_INTERRUPT BIT(2)
#define IER_CLEAR_INTERRUPTS 0xF8 // clears only the first 3 bits of the IER

/**
 * @brief The offset of the FIFO Control Register (FCR) from the base address of a UART serial port, when this address is accessed for writing.
 */
#define FCR_OFFSET 2

/**
 * @brief The bit of FCR for enabling the FIFOs (receiver and transmitter).
 */
#define FCR_ENABLE_FIFO BIT(0)

/**
 * @brief The bit for clearing the receiver FIFO of FCR.
 */
#define FCR_CLEAR_RECEIVER_FIFO BIT(1)

/**
 * @brief The bit for clearing the transmitter FIFO of FCR.
 */
#define FCR_CLEAR_TRANSMITTER_FIFO BIT(2)

/**
 * @brief Mask to clear the bits relative to the FIFOs of the FCR.
 */
#define FCR_CLEAR_FIFOS 0xF8

/**
 * @brief The offset of the Line Control Register (LCR) from the base address of a UART serial port.
 */
#define LCR_OFFSET 3

#define LCR_CHAR_LENGTH_6 BIT(0)
#define LCR_CHAR_LENGTH_7 BIT(1)
#define LCR_CHAR_LENGTH_8 BIT(1) | BIT(0)

#define LCR_STOP_BIT_2 BIT(2)

#define LCR_ODD_PARITY BIT(3)
#define LCR_EVEN_PARITY BIT(4) | BIT(3)
#define LCR_FORCED1_PARITY BIT(5) | BIT(3)
#define LCR_FORCED0_PARITY BIT(5) | BIT(4) | BIT(3)

#define LCR_CLEAR_EXCEPT_BREAK_CONTROL 0x40

/**
 * @brief The offset of the Divisor Latch LSB (DLL) register from the base address of a UART serial port when DLAB bit of the LCR is set.
 */
#define DLL_OFFSET 0

/**
 * @brief The offset of the Divisor Latch MSB (DLM) register from the base address of a UART serial port when DLAB bit of the LCR is set.
 */
#define DLM_OFFSET 1

/**
 * @brief The bit relative to the DLAB (Divisor Latch Access Bit) in the Line Control Register (LCR) of the serial port. This bit must be set to 1 to access the divisor registers (DLL and DLM) and set the bit rate of the serial port.
 */
#define LCR_DLAB BIT(7)

/**
 * @brief Sets up both the receiver and transmitter FIFOs of the serial port, by writing to the FIFO Control Register (FCR) of the serial port, with the appropriate bits set.
 * @return 0 on success, 1 on failure
 */
int setup_fifos();

int setup_lcr();

// To set up the Interrupt Enable Register (IER) of the serial port. Activate only the necessary bits to enable the desired interrupts.
int setup_ier();

/**
 * @brief Enables the Received Data Available Interrupt of the IER of the serial port, which allows the serial port to generate an interrupt whenever there is data available to be read from the Receiver Buffer Register (RBR) of the serial port.
 * @return 0 on success, 1 on failure
 */
int enable_received_data_interrupt();

/**
 * @brief Enables the Transmitter Holding Register Empty Interrupt of the IER of the serial port, which allows the serial port to generate an interrupt whenever the Transmitter Holding Register (THR) of the serial port is empty and ready to accept new data to be transmitted.
 * @return 0 on success, 1 on failure 
 */
int enable_transmitter_holding_register_empty_interrupt();

/**
 * @brief Enables the Line Status Interrupt of the IER of the serial port, which allows the serial port to generate an interrupt whenever there is a change in the error bits of the Line Status Register (LSR).
 * @return 0 on success, 1 on failure
 */
int enable_line_status_interrupt();

int get_fcr(uint8_t *fcr);
int get_ier(uint8_t *ier);
int get_lcr(uint8_t *lcr);

int set_bit_rate(uint16_t bit_rate);

// Uses flag IRQ_EXCLUSIVE because MINIX has a default interrupt handler for the UART.
int serial_port_subscribe_int(uint8_t *bit_no);

int setup_serial_port();

int serial_port_unsubscribe_int();
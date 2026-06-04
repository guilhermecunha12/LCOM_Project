#include "serial_port.h"

// These are defined here, so they can be easily modified
#define CHAR_LENGTH 8
#define STOP_BITS 1
#define PARITY 2 // Even parity
#define BIT_RATE 10

static int serial_port_hook_id;
static uint8_t received_data;

int setup_fifos() {
    uint8_t fcr = 0x00;
    fcr |= FCR_ENABLE_FIFO | FCR_CLEAR_RECEIVER_FIFO | FCR_CLEAR_TRANSMITTER_FIFO;
    fcr &= FCR_1BYTE_TRIGGER_LEVEL;
    return sys_outb(COM1_BASE + FCR_OFFSET, fcr);
}

int setup_lcr(int char_length, int stop_bits, int parity) {
    
    uint8_t lcr;

    // Set character length
    switch (char_length) {
        case 5: 
            /* No bits set */
            break;

        case 6:
            lcr |= LCR_CHAR_LENGTH_6;
            break;

        case 7:
            lcr |= LCR_CHAR_LENGTH_7;
            break;
        
        case 8:
            lcr |= LCR_CHAR_LENGTH_8;
            break;

        default:
            break;
    }

    // Set stop bits
    switch (stop_bits) {
        case 1:
            /* No bits set */
            break;

        case 2:
            lcr |= LCR_STOP_BIT_2;
            break;

        default:
            break;
    }

    // Set parity
    switch (parity) {
        case 0: 
            /* No bits set */
            break;

        case 1: // Odd parity
            lcr |= LCR_ODD_PARITY; 
            break;

        case 2: // Even parity
            lcr |= LCR_EVEN_PARITY; 
            break;

        case 3: // Forced 1 parity
            lcr |= LCR_FORCED1_PARITY;
            break;
        
        case 4: // Forced 0 parity
            lcr |= LCR_FORCED0_PARITY;
            break;

        default:
            break;
    }

    return sys_outb(COM1_BASE + LCR_OFFSET, lcr);
}

int enable_received_data_interrupt() {
    uint8_t ier;
    if (get_ier(&ier)) return 1;
    ier |= IER_RECEIVED_DATA_AVAILABLE_INTERRUPT;
    return sys_outb(COM1_BASE + IER_OFFSET, ier);
}

//TODO: remove
int enable_transmitter_holding_register_empty_interrupt() {
    uint8_t ier;
    if (get_ier(&ier)) return 1;
    ier |= IER_TRANSMITTER_HOLDING_REGISTER_EMPTY_INTERRUPT;
    return sys_outb(COM1_BASE + IER_OFFSET, ier);
}

int enable_line_status_interrupt() {
    uint8_t ier;
    if (get_ier(&ier)) return 1;
    ier |= IER_LINE_STATUS_INTERRUPT;
    return sys_outb(COM1_BASE + IER_OFFSET, ier);
}

int get_fcr(uint8_t *fcr) {
    return util_sys_inb(COM1_BASE + FCR_OFFSET, fcr);
}

int get_ier(uint8_t *ier) {
    return util_sys_inb(COM1_BASE + IER_OFFSET, ier);
}

int get_lcr(uint8_t *lcr) {
    return util_sys_inb(COM1_BASE + LCR_OFFSET, lcr);
}

int get_iir(uint8_t *iir) {
    return util_sys_inb(COM1_BASE + IIR_OFFSET, iir);
}

int get_lsr(uint8_t *lsr) {
    return util_sys_inb(COM1_BASE + LSR_OFFSET, lsr);
}

int set_bit_rate(uint16_t bit_rate) {
    // Set DLAB bit to access the divisor registers
    uint8_t lcr;
    if (get_lcr(&lcr)) return 1;
    lcr |= LCR_DLAB;

    if (sys_outb(COM1_BASE + LCR_OFFSET, lcr)) return 1;

    uint16_t divisor = DIVIDED_CLOCK_FREQUENCY / bit_rate;
    uint8_t divisor_msb, divisor_lsb;

    // Get the LSB and MSB of the divisor
    if (util_get_LSB(divisor, &divisor_lsb)) return 1;
    if (util_get_MSB(divisor, &divisor_msb)) return 1;

    // Write the divisor to the LSB and MSB registers of the serial port
    if (sys_outb(COM1_BASE + DLL_OFFSET, divisor_lsb)) return 1;
    if (sys_outb(COM1_BASE + DLM_OFFSET, divisor_msb)) return 1;

    // Clear DLAB because we are done configuring the divisor latch registers
    if (sys_outb(COM1_BASE + LCR_OFFSET, lcr & ~LCR_DLAB)) return 1;

    return 0;
}

int serial_port_subscribe_int(uint8_t *bit_no) {
    serial_port_hook_id = *bit_no;
    if (sys_irqsetpolicy(IRQ_COM1, IRQ_REENABLE | IRQ_EXCLUSIVE, &serial_port_hook_id)) return 1;
    *bit_no = BIT(*bit_no);
    return 0;
}

int setup_serial_port_receiver(uint8_t *bit_no) {
    if (setup_fifos()) return 1;
    if (setup_lcr(CHAR_LENGTH, STOP_BITS, PARITY)) return 1;
    if (enable_received_data_interrupt()) return 1;
    if (enable_line_status_interrupt()) return 1;
    if (set_bit_rate(BIT_RATE)) return 1;
    if (serial_port_subscribe_int(&bit_no)) return 1;
    return 0;
}

int setup_serial_port_transmitter(uint8_t *bit_no) {
    if (setup_fifos()) return 1;
    if (setup_lcr(CHAR_LENGTH, STOP_BITS, PARITY)) return 1;
    if (enable_line_status_interrupt()) return 1;
    if (set_bit_rate(BIT_RATE)) return 1;
    if (serial_port_subscribe_int(&bit_no)) return 1;
    return 0;
}

int serial_port_unsubscribe_int() {
    return sys_irqrmpolicy(&serial_port_hook_id) ? 1 : 0;
}

int serial_port_undo() {
    if (serial_port_unsubscribe_int()) return 1; // Unsubscribe from serial port interrupts

    uint8_t fcr;
    if (get_fcr(&fcr)) return 1;
    if (sys_outb(COM1_BASE + FCR_OFFSET, fcr & FCR_CLEAR_FIFOS)) return 1; // Disable FIFOs

    uint8_t lcr;
    if (get_lcr(&lcr)) return 1;
    if (sys_outb(COM1_BASE + LCR_OFFSET, lcr & LCR_CLEAR_EXCEPT_BREAK_CONTROL)) return 1; // Clear LCR configuration, except for the break control bit

    uint8_t ier;
    if (get_ier(&ier)) return 1;
    if (sys_outb(COM1_BASE + IER_OFFSET, ier & IER_CLEAR_INTERRUPTS)) return 1; // Disable interrupts
    return 0;
}

uint8_t get_received_data() {
    return received_data;
}

int send_data(uint8_t data) {
    uint8_t lsr;
    if (get_lsr(&lsr)) return 1;

    // Wait until THR is empty
    while ((lsr & LSR_TRANSMITTER_HOLDING_REGISTER_EMPTY) == 0) {
        if (get_lsr(&lsr)) return 1;
    }

    // Send the data by writing it to the Transmitter Holding Register (THR) of the serial port
    return sys_outb(COM1_BASE + THR_OFFSET, data);
}

int serial_port_ih() {
    // Read the IIR to determine the source of the interrupt
    uint8_t iir;
    if (get_iir(&iir)) return 1;

    if (iir & IIR_NO_INTERRUPT_PENDING) return 1;

    uint8_t interrupt_type = IIR_INTERRUPT_TYPE(iir);
    uint8_t lsr;

    if (interrupt_type == IIR_RECEIVER_LINE_STATUS_INTERRUPT) {
        // Read the Line Status Register to clear the interrupt (datasheet)
        get_lsr(&lsr);
        return 1;

    } else if (interrupt_type == IIR_RECEIVED_DATA_AVAILABLE_INTERRUPT || interrupt_type == IIR_CHARACTER_TIMEOUT_INTERRUPT) {
        // Read the received data from the Receiver Buffer Register (RBR)
        // Handle character timeout interrupt the same way as received data available interrupt.
        
        // Check for errors in the LSR error bits
        if (get_lsr(&lsr)) return 1;
        if (lsr & (LSR_OVERRUN_ERROR | LSR_PARITY_ERROR | LSR_FRAMING_ERROR)) return 1;

        // Check if the FIFOS are enabled by checking FIFO related bits in the IIR (TODO: can be wrong)
        if (!(iir & IIR_FIFOS_ENABLED)) return 1;

        if (lsr & LSR_DATA_READY) {
            if (util_sys_inb(COM1_BASE + RBR_OFFSET, &received_data)) return 1;
        }

    } else {
        return 1; // Unexpected interrupt type
    }

    return 0;
}

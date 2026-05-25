#ifndef KBC_H
#define KBC_H

#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

/**
 * @brief Keyboard interrupt handler.
 * @details This function is called when a keyboard interrupt occurs. Called through process_scancode(), it simply reads a byte from the KBC output buffer and updates the last_byte_read variable, which is later used to build the scancode array. Only considers valid reads, as read_scancode() must return 0.
 */
void (kbc_ih) ();

/**
 * @brief Function to subscribe to keyboard interrupts.
 * @details The value of *bit_no can never be greater than 7, otherwise, an overflow will occur when updating it with the bit mask.
 * @param bit_no Initially, a pointer to the bit position in the interrupt mask to be set to 1 in case of an interrupt. On success, its value is updated with the corresponding bit mask with a 1 in the *bit_no position (i.e., 1 << *bit_no).
 * @return int Returns 0 on success, 1 otherwise.
 */
int kbd_subscribe_int(uint8_t* bit_no);

/**
 * @brief Function to unsubscribe from keyboard interrupts.
 * @return int Returns 0 on success, 1 otherwise.
 */
int kbd_unsubscribe_int();

/**
 * @brief Reads a scancode from the KBC output buffer.
 * @details This function reads a single byte from the KBC output buffer and stores it in the provided variable.
 * @param byte Pointer to the variable where the read byte will be stored.
 * @return int 0 if successful, 1 otherwise.
 */
int read_scancode(uint8_t *byte);

/**
 * @brief Getter function to access the scancode array.
 * @details This function returns a pointer to the scancode array.
 * @return uint8_t* Pointer to the scancode array.
 */
uint8_t* get_scancode();

/**
 * @brief Getter function to access the last byte read from the KBC output buffer.
 * @details This function returns the last byte read from the KBC output buffer.
 * @return uint8_t The last byte read from the KBC output buffer.
 */
uint8_t get_last_byte_read();

/**
 * @brief Function to determine if a scancode is a make or break code.
 * @details A scancode is a make code if its most significant bit is 0, and a break code if the most significant bit is 1.
 * @param scancode Pointer to the scancode array.
 * @return uint8_t 1 if it's a make code, 0 if it's a break code.
 */
uint8_t is_make_code(uint8_t scancode[2]);

/**
 * @brief Function that writes a command byte to a specified port, with retries if the KBC input buffer is full.
 * @details This function attempts to write a command byte to a specified port.
 * @param port The port to which the command byte should be written.
 * @param command_byte The command byte to be written to the specified port.
 * @return int 0 if the command byte was successfully written, 1 otherwise.
 */
int write_KBC_command(uint8_t port, uint8_t command_byte);

/**
 * @brief Function to read a byte from the KBC output buffer.
 * @details This function reads a single byte from the KBC output buffer and stores it in the provided variable. Since both the keyboard and mouse data are read from the same output buffer, the mouse_data flag is used to indicate whether we want to read mouse data or keyboard data.
 * @param value Pointer to the variable where the read byte will be stored.
 * @param mouse_data Flag indicating whether to read mouse data.
 * @return int 0 if successful, 1 otherwise.
 */
int read_KBC_output_buf(uint8_t* value, bool mouse_related_data);

/**
 * @brief Function to reset the KBC interrupts (turns them back on).
 * @details In case of polling, the KBC interrupts are naturally turned off, so this function is used to turn them back on. It does so by issuing a read command byte to the command register, allowing to read the internal settings of the KBC and then setting the bit corresponding to enabling keyboard interrupts before writing the new command byte back to the KBC.
 * @return int 0 if successful, 1 otherwise.
 */
int reset_interrupts();

/**
 * @brief Function to process a key's scancode (one or two bytes).
 * @details This function is responsible for the bulk of work related to processing a scancode. Works as a higher level wrapper, abstracting lower level details by using the other functions defined in this file.
 * Calls the interrupt handler defined above to read the current byte issued from the KBC and available in the output buffer, then checks whether it's a single-byte or two-byte scancode and populates the scancode array accordingly.
 * @return true if the scancode has been completely read (whether it's a single-byte or two-byte scancode)
 * @return false if we are still reading a two-byte scancode 
 */
bool process_scancode();


#endif

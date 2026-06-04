#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include "i8042_mouse.h"

/**
 * @brief Subscribes and enables mouse interrupts.
 * @details The value of *bit_no can never be greater than 7, otherwise, an overflow will occur when updating it with the bit mask.
 * @param bit_no Initially, a pointer to the bit position in the interrupt mask to be set to 1 in case of an interrupt. On success, its value is updated with the corresponding bit mask with a 1 in the *bit_no position (i.e., 1 << *bit_no).
 * @return Returns 0 on success, 1 otherwise.
 */
int mouse_subscribe_int(uint8_t* bit_no);

/**
 * @brief Unsubscribes mouse interrupts.
 * @return Returns 0 on success, 1 otherwise.
 */
int mouse_unsubscribe_int();

/**
 * @brief Getter for the mouse packet, which may be complete or being read (i.e., not all bytes have been read yet).
 * @return the value of the pp variable, which is a struct packet struct that contains the bytes parsed so far.
 */
struct packet get_mouse_packet();

/**
 * @brief Mouse interrupt handler.
 * @details Reads the byte from the output buffer of the KBC and updates the mouse_byte variable with it.
 */
void (mouse_ih) ();

// Functions to enable/disable data packets being sent on the go

/**
 * @brief Generic function to send a command directly into the mouse.
 * @details Before sending any command to the mouse, data reporting is disabled to prevent interference from packets sent by the mouse. After sending the command, data reporting is reenabled. The function also checks if the command was acknowledged by the mouse and retries if not.
 * @param cmd the command to be sent to the mouse.
 * @return Returns 0 on success, 1 otherwise.
 */
int send_to_mouse(uint8_t cmd);

/**
 * @brief Enable mouse data reporting with the appropriate command (0xF4).
 * @return Returns 0 on success, 1 otherwise.
 */
int enable_mouse_data_reporting();

/**
 * @brief Disable mouse data reporting with the appropriate command (0xF5).
 * @return Returns 0 on success, 1 otherwise.
 */
int disable_mouse_data_reporting(); 

/**
 * @brief Computes a coordinate's delta (x or y) of the mouse's movement in a 16-bit sign-extended integer.
 * @details In reality, the delta has only 9 bits (the 8 bits of the mouse byte plus the sign bit), but it is stored in a 16-bit integer for memory-alignment.
 * @param sign_bit the sign bit of the coordinate's delta, which is obtained from the first byte of the mouse packet. If the sign bit is 1, the delta is negative and needs to be sign-extended; otherwise, it is positive.
 * @param mouse_byte the byte from the mouse packet that contains the least significant byte of the coordinate's delta.
 * @return the computed delta as a 16-bit signed integer.
 */
int16_t get_delta(bool sign_bit, uint8_t mouse_byte);

/**
 * @brief Parses the first byte of a data packet received by the mouse and populates fields of a packet struct and sign bits variables.
 * @param pp Pointer to the packet struct to be populated.
 * @param x_sign_bit Pointer to the variable that will store the sign bit for the x coordinate.
 * @param y_sign_bit Pointer to the variable that will store the sign bit for the y coordinate.
 * @param mouse_byte The byte from the mouse packet that contains the first byte of the data packet.
 */
void parse_first_byte(struct packet* pp, bool* x_sign_bit, bool* y_sign_bit, uint8_t mouse_byte);


/**
 * @brief Checks if the current mouse packet corresponds to a mouse left button click.
 * @return true if the left button is pressed in the current mouse packet, false otherwise.
 */
bool is_mouse_click();

/**
 * @brief Checks if the current mouse packet corresponds to a mouse movement (i.e., if there is any non-zero delta in the x or y coordinates).
 * @return true if there is a movement in the current mouse packet, false otherwise.
 */
bool is_mouse_move();

/**
 * @brief Performs a step in processing a mouse packet.
 * @details This functions is called every time a new interrupt is received from the mouse and reads the new byte of the packet, updates the packet struct being read, and checks if the packet is complete (i.e., all bytes have been read). The uses a static variable byte_index to keep track of the current byte being read (0, 1 or 2) and updates it accordingly. When a packet is complete, the function resets byte_index to 0 to start reading the next packet. The function uses a naive way to find out the beginning of data packets, which is to check if the 3rd bit of the first byte is set (as it should be for the first byte of any packet) when it is waiting for the first byte (i.e., byte_index == 0). 
 * @return true if the packet is ready (fully read) and false otherwise.
 */
bool process_packet();

#endif

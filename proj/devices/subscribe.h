#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include "../../lab2/timer_count.h"
#include "../../lab3/kbc.h"
#include "../../lab4/mouse.h"
#include "../../lab5/video.h"


#define IRQ_TIMER 0
#define IRQ_KBD 1
#define IRQ_MOUSE 2
#define IRQ_COM1 4


int subscribe_receiver_devices(uint8_t* kbd_bit_no, uint8_t *com1_bit_no, uint16_t vbe_mode);

/**
 * @brief Subscribes to the timer, keyboard and mouse interrupts and sets the VBE mode. If any of the operations fail, it unsubscribes from all devices and returns 1. Otherwise, it returns 0.
 * @param timer_bit_no Pointer to the variable that will store the bit number of the timer interrupt.
 * @param kbd_bit_no Pointer to the variable that will store the bit number of the keyboard interrupt.
 * @param mouse_bit_no Pointer to the variable that will store the bit number of the mouse interrupt.
 * @param com1_bit_no Pointer to the variable that will store the bit number of the COM1 interrupt.
 * @param vbe_mode The VBE mode to set.
 * @return 0 if all operations were successful, 1 otherwise.
 */

 int subscribe_devices(uint8_t *timer_bit_no, uint8_t *kbd_bit_no, uint8_t *mouse_bit_no, uint8_t *com1_bit_no, uint16_t vbe_mode);

int unsubscribe_receiver_devices();

 /**
 * @brief Unsubscribes from the timer, keyboard and mouse interrupts and exits the VBE mode. If any of the operations fail, it returns 1. Otherwise, it returns 0.
 * @return 0 if all operations were successful, 1 otherwise.
 */
int unsubscribe_devices();

#endif /* SUBSCRIBE_H */

#include "lab2/timer_count.h"
#include "lab3/kbc.h"
#include "lab4/mouse.h"
#include "lab5/video.h"

/**
 * @brief Subscribes to the timer, keyboard and mouse interrupts and sets the VBE mode. If any of the operations fail, it unsubscribes from all devices and returns 1. Otherwise, it returns 0.
 * @param timer_bit_no Pointer to the variable that will store the bit number of the timer interrupt.
 * @param kbd_bit_no Pointer to the variable that will store the bit number of the keyboard interrupt.
 * @param mouse_bit_no Pointer to the variable that will store the bit number of the mouse interrupt.
 * @param vbe_mode The VBE mode to set.
 * @return 0 if all operations were successful, 1 otherwise.
 */
int subscribe_devices(uint8_t *timer_bit_no, uint8_t *kbd_bit_no, uint8_t *mouse_bit_no, uint16_t vbe_mode) {

  if (timer_subscribe_int(timer_bit_no)) return 1;
  if (kbd_subscribe_int(kbd_bit_no))   { timer_unsubscribe_int(); return 1; }
  if (mouse_subscribe_int(mouse_bit_no)) { timer_unsubscribe_int(); 
                                            kbd_unsubscribe_int(); return 1; }
  if (vg_set_mode(vbe_mode)) { timer_unsubscribe_int(); kbd_unsubscribe_int(); 
                                mouse_unsubscribe_int(); return 1; }

  return 0;
}

/**
 * @brief Unsubscribes from the timer, keyboard and mouse interrupts and exits the VBE mode. If any of the operations fail, it returns 1. Otherwise, it returns 0.
 * @return 0 if all operations were successful, 1 otherwise.
 */
int unsubscribe_devices() {
  int err = 0;
  err |= timer_unsubscribe_int();
  err |= kbd_unsubscribe_int();
  err |= mouse_unsubscribe_int();
  err |= vg_exit();

  return err;
}

// Example main function.
int main(int argc, char *argv[]) {
  // Default values for bit num of all devices and VBE mode.
  uint8_t timer_bit_no = 0;
  uint8_t kbd_bit_no = 1;
  uint8_t mouse_bit_no = 2;
  uint16_t vbe_mode = 0x11B; //for now

  // Subscribe 
  if(subscribe_devices(&timer_bit_no, &kbd_bit_no, &mouse_bit_no, vbe_mode)) return 1;

  // Unsubscribe
  if(unsubscribe_devices()) return 1;
  return 0;
}

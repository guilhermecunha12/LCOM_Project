#include "subscribe.h"
#include "../game_constants.h"

int subscribe_devices(uint8_t *timer_bit_no, uint8_t *kbd_bit_no, uint8_t *mouse_bit_no, uint8_t *com1_bit_no, uint16_t vbe_mode) {

  timer_set_frequency(0, FPS); // Set timer 0 to the desired frequency for consistent game timing
  if (timer_subscribe_int(timer_bit_no)) return 1;

  if (kbd_subscribe_int(kbd_bit_no)) {
    timer_unsubscribe_int();
    return 1;
  }

  if (mouse_subscribe_int(mouse_bit_no)) {
    timer_unsubscribe_int(); 
    kbd_unsubscribe_int(); return 1;
  }

  if (serial_port_subscribe_int(com1_bit_no)) {
    timer_unsubscribe_int();
    kbd_unsubscribe_int();
    mouse_unsubscribe_int();
    return 1;
  }

  if (init_video_card(vbe_mode)) {
    timer_unsubscribe_int();
    kbd_unsubscribe_int();
    mouse_unsubscribe_int();
    serial_port_unsubscribe_int();
    return 1;
  }

  return 0;
}

int unsubscribe_devices() {
  int err = 0;
  err |= timer_unsubscribe_int();
  err |= kbd_unsubscribe_int();
  err |= reset_interrupts();
  err |= mouse_unsubscribe_int();
  err |= vg_exit();

  return err;
}


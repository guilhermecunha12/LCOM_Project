#include "subscribe.h"
#include "../game_constants.h"
#include "serial_port/serial_port.h"

int subscribe_receiver_devices(uint8_t* kbd_bit_no, uint8_t *com1_bit_no, uint16_t vbe_mode) {

  if (kbd_subscribe_int(kbd_bit_no)) {
    return 1;
  }

  if (setup_serial_port_receiver(com1_bit_no)) {
    kbd_unsubscribe_int();
    return 1;
  }

  if (init_video_card(vbe_mode)) {
    kbd_unsubscribe_int();
    serial_port_undo();
    return 1;
  }

  return 0;
}

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

  if (setup_serial_port_transmitter(com1_bit_no)) {
    timer_unsubscribe_int();
    kbd_unsubscribe_int();
    mouse_unsubscribe_int();
    return 1;
  }

  if (init_video_card(vbe_mode)) {
    timer_unsubscribe_int();
    kbd_unsubscribe_int();
    mouse_unsubscribe_int();
    serial_port_undo();
    return 1;
  }

  return 0;
}

int unsubscribe_receiver_devices() {
  int err = 0;
  err |= kbd_unsubscribe_int();
  err |= reset_interrupts();
  err |= vg_exit();

  return err;
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


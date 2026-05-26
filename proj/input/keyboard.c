#include "keyboard.h"

/**
 * @brief Get the mapped key from the scancode.
 * @details This function takes a scancode and returns the corresponding mapped key. It normalizes the scancode by converting break codes to make codes, since we only care about which key was pressed, not if it was a press or release (that's already been stored in the event type). 
 * @param scancode The scancode array containing the scancode bytes.
 * @return Key The mapped key corresponding to the scancode.
 */
static Key get_key(uint8_t scancode[2]) {
  uint8_t normalized_scancode = scancode[1];
  if (!is_make_code(scancode)) {
    normalized_scancode &= 0x7F;
  }

  switch (normalized_scancode) {
    case 0x48: // Up arrow
      return KEY_MENU_UP;
    case 0x50: // Down arrow
      return KEY_MENU_DOWN;
    case 0x4B: // Left arrow
      return KEY_LEFT;
    case 0x4D: // Right arrow
      return KEY_RIGHT;
    case 0x1C: // Enter key
      return KEY_ENTER;
    case 0x39: // Space key
      return KEY_SPACE;
    case 0x01: // Escape key
      return KEY_ESCAPE;
    default:
      return -1; // Return -1 for unmapped keys, should be handled by the caller
  }
}

int update_game_event(GameEvent* ge){
  if (!process_scancode()) {
    return -1;
  }

  uint8_t* scancode = get_scancode();
  Key key = get_key(scancode);
  if (key == -1) {
    return -1;
  }

  ge->type = is_make_code(scancode) ? KEYBOARD_PRESS : KEYBOARD_RELEASE;
  ge->data.key = key;
  return 0;
}
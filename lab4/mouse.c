// Probably will be able to use the same ideas for the mouse functions

// Errors: 
// 0xFE -> signals an error meaning will have to resend the entire command from the beginning
// 0xFC -> should also attempt to resend the entire command, not just the argument byte

// Acknowledgement byte -> 0xFA -> indicates that the mouse has successfully recieved the byte and is ready for the next one (doesnt necessarily indicates that the command has been fully executed)

// Important, check the KBC status register before writing to 0x60 and 0x64 (not full and safe to write). Also check that the output buffer is not full and it is safe to write to (no parity or timeout errors)

// Before sending any command to the mouse, disable data reporting to prevent interference from packets sent by the mouse

// Check mouse data packets that will be returned, in this case, 3 bytes at a time, but need to find a way to be able to interpret each 3 byte "batch"

#include <lcom/lcf.h>
#include "lab3/i8042.h"
#include "lab3/kbc.h"
#include "mouse.h"

static uint8_t mouse_byte; // static variable that could be accessed anywhere in the file

// Also need to implement subscribe and unsubscribe for the keyboard

void set_mouse_byte(uint8_t data){
  mouse_byte = data;
}

uint8_t get_mouse_byte(){
  return mouse_byte;
}

// The function will be responsible by reading the byte from the buffer and then updating 
void (mouse_ih) () {
  uint8_t mouse_data;
  if(read_KBC_output_buf(&mouse_data, true)) return;
  set_mouse_byte(mouse_data);
}
#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

extern int global_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  // Similar to test_scan
  int ipc_status;
  message msg;
  // Timer 0 interrupt bit, used for the idle time
  uint8_t timer0_int_bit = 0;

  // Keyboard interrupt bit
  uint8_t kbd_int_bit = 1;

  // Time ellapsed since the last keybaord interrupt
  int idle = 0;

  // Subscribe timer interrupts
  if(timer_subscribe_int(&timer0_int_bit)){
    return 1;
  }

  // Subscribe keyboard interrupts
  if (kbd_subscribe_int(&kbd_int_bit)){
    return 1;
  }

  int r;

  // Break the while loop if ESC breakcode is received, or if keyboard didnt generated any interrupt in n seconds
  while((idle < n * 60) && get_scancode() != 0x81){
    // não é 1, ou ESC ou n seconds
    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    if(is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if(msg.m_notify.interrupts & timer0_int_bit){
            // Timer 0 interrupt
            idle++;
          }
          if(msg.m_notify.interrupts & kbd_int_bit){
            kbc_ih();
            idle = 0;
          }
          break;
        default:
          break;
      }
    }else{
       
    }
  }

  // unsubscribe timer0
  if(timer_unsubscribe_int()){
    return 1;
  }

  //unsubscribe keyboard
  if(kbd_unsubscribe_int()){
    return 1;
  }

  return 0;
}
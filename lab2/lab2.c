#include <lcom/lcf.h>
#include <lcom/lab2.h>
#include <lcom/timer.h>
#include <stdbool.h>
#include <stdint.h>

extern int global_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

// Read and display a field of the status byte
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t status_byte;

  // Read the status byte at the timer's port
  if (timer_get_conf(timer, &status_byte)) { 
    return 1;
  }

  // Displays the specified field of the status byte
  if (timer_display_conf(timer, status_byte, field)) {
    return 1;
  }

  return 0;
}

// Changes a timer's time base (frequency of interrupts)
int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  return timer_set_frequency(timer, freq);
}


// subscribe, handle, unsubscribe
// time: how long the function timer_print_elapsed_time will be invoked (once per second)
// hook_id passed to irqsetpolicy -> bit position in the message bitmask
// hook_id "returned"/modified by irqsetpolicy -> internal value used by the GIH (like a file descriptor)
int(timer_test_int)(uint8_t time) {
   uint32_t t = time * 60; // because it is the default frequency
  int ipc_status;
  message msg;
  int bit_no = 0; // this function (caller) should initialize it with a int value (that will be the index position of the bit relative to this device driver in m_notify.interrupts)
  timer_subscribe_int(&bit_no); // IMPORTANT: after this function call, the value of bit_no is not a bit index anymore, but a mask to apply to the received message to get the value of the IRQ line of the timer
  int r; // return value of the driver_receive function

  while( t > 0 ) { /* You may want to use a different condition */
      /* Get a request message. */
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
      }

      if (is_ipc_notify(ipc_status)) { /* received notification */
          switch (_ENDPOINT_P(msg.m_source)) { // allows to extract the process identifier from a process’s endpoint
              case HARDWARE: /* hardware interrupt notification */        
                  if (msg.m_notify.interrupts & bit_no) { /* subscribed interrupt */
                    timer_int_handler();
                    if (t % 60 == 0) {
                      timer_print_elapsed_time();
                    }
                    t--;
                  }
                  break;
              default:
                  break; /* no other notifications expected: do nothing */  
          }
      } else { /* received a standard message, not a notification */
          /* no standard messages expected: do nothing */
      }
  }

  timer_unsubscribe_int();
  return 0;
}

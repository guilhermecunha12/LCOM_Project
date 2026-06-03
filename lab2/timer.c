#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "timer_count.h"

#include <stdint.h>

#include "i8254.h"

/**
 * @brief Global counter variable to track the number of timer interrupts that have occurred.
 * @details Incremented by the timer interrupt handler. Can be accessed and modified using get_counter() and set_counter() functions. Initialized to 0 at the start of the program.
 */
static int global_counter = 0;

/**
 * @brief The interrupt hook ID for the timer.
 * @details Used for subscribing and unsubscribing timer interrupts. Initially defined in timer_subscribe_int() and used in timer_unsubscribe_int().
 */
int hook_id; 

int get_counter(){
  return global_counter;
}

void set_counter(int n){
  global_counter = n;
}

/**
 * @brief Sets the operating frequency of the specified timer.
 * @details This function calculates the appropriate divider value based on the desired frequency and the base frequency of the timer. It then constructs a control byte to configure the timer's mode and writes it to the control register, followed by writing the LSB and MSB of the divider to the timer's counter register. The function also retrieves the current configuration of the timer to preserve certain bits when setting the new frequency.
 * @param timer The timer to configure (0, 1, or 2).
 * @param freq The desired frequency in Hz. Must be less than TIMER_FREQ (1193182 Hz).
 * @return 0 on success, 1 on failure.
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq) { 
  int target_port = TIMER_0 + timer;
  uint8_t status_byte;
  timer_get_conf(timer, &status_byte);
  uint8_t control_byte =  (timer << 6) | TIMER_LSB_MSB | (status_byte & 0x0F); // build control byte to configure our timer

  if(sys_outb(TIMER_CTRL,control_byte)) return 1; // write control_byte to control_register

  uint16_t divider = (uint16_t) (TIMER_FREQ / freq);
  uint8_t lsb, msb; 
  // Write in the specified order defined in the control byte (LSB followed by MSB)
  util_get_LSB(divider,&lsb);
  util_get_MSB(divider,&msb);

  if(sys_outb(target_port,lsb) !=0 || sys_outb(target_port,msb) !=0) return 1;
 
  return 0;
}

// Subscribe the interrupts for a given IRQ Line 
// Change the content of the given pointer to have the mask containing the active subscribed IRQ
/**
 * @brief Subscribes to timer interrupts.
 * @return 0 on success, 1 on failure.
 */
int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  if(sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id)) return 1;
  *bit_no = BIT(*bit_no);
  return 0;
}

/**
 * @brief Unsubscribes from timer interrupts.
 * @return 0 on success, 1 on failure.
 */
int (timer_unsubscribe_int)() {
  // Disables interrupts on hook_id associated
  if(sys_irqrmpolicy(&hook_id)) return 1;
  return 0;
}

/**
 * @brief Timer interrupt handler function.
 * @details This function is called whenever a timer interrupt occurs. It increments the global counter variable to keep track of the number of interrupts that have occurred.
 */
void (timer_int_handler)() {
  global_counter++;
}

/**
 * @brief Gets the configuration of the specified timer.
 * @details This function retrieves the current configuration of the specified timer and stores it in the provided pointer. It constructs a read-back command to request the timer's status and sends it to the control register. Then, it reads the status byte from the timer's counter register and stores it in the provided pointer.
 * @param timer The timer to retrieve configuration for (0, 1, or 2).
 * @param st Pointer to store the retrieved configuration.
 * @return 0 on success, 1 on failure.
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t read_back_command = 0;
  read_back_command |= TIMER_RB_CMD;
  read_back_command |= TIMER_RB_COUNT_;
  read_back_command |= TIMER_RB_SEL(timer);
  if (sys_outb(TIMER_CTRL, read_back_command)){
    return 1;
  };
  int port = TIMER_0 + timer;
  if(util_sys_inb(port, st)) {
    return 1;
  };
  return 0;
}

/**
 * @brief Displays the configuration of the specified timer.
 * @details This function retrieves the configuration of the specified timer and displays it according to the specified field.
 * @param timer The timer to display configuration for (0, 1, or 2).
 * @param st The configuration byte to display.
 * @param field The field to display.
 * @return 0 on success, 1 on failure.
 */
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  timer_get_conf(timer, &st);
  union timer_status_field_val conf;

  // field says what to display in the conf
  switch(field){
    case tsf_all:
      /* Display status byte, in hexadecimal */
      conf.byte = st;
      break;

    case tsf_initial:
      /* Display the initialization mode only */
      // Extract the Initialization Mode bits and shift them to convert to int for the enum
      conf.in_mode = (st & TIMER_LSB_MSB) >> 4; 
      break;

    case tsf_mode:
      /* Display the counting mode, only */

      // Get the couting mode bits (3,2,1), first shifting them to the right
      conf.count_mode = (uint8_t)((st >> 1) & 0x7); 

      // Special cases
      // 111* -> 3
      // 110* -> 2

      if (conf.count_mode == 7){
        conf.count_mode = 3;
      } else if (conf.count_mode == 6){
        conf.count_mode = 2;
      }
      break;

    case tsf_base:
      /* Display the counting base, only */
      // See if it's in BCD
      conf.bcd = (st & TIMER_BCD);
      break;

    default:
      printf("Unknown field\n");
      return 1;
  }

  return timer_print_config(timer, field, conf);
}

#include <lcom/lcf.h>
// This header file is used make timer.a overwrite the liblfc.a deafult defnition of timer.h

/**
 * @brief Function to get the value of the global counter variable.
 */
int get_counter();

/**
 * @brief Function to set the value of the global counter variable.
 * @param n The value to set the counter to.
 */
void set_counter(int n);

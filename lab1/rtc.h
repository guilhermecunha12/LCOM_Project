#pragma once

#include <stdint.h>

typedef struct {
  uint8_t day;
  uint8_t month;
  uint8_t year;
} rtc_date;

/**
 * Reads the current date from the RTC and fills the provided `rtc_date`
 * structure. Returns 0 on success, non-zero on failure.
 *
 * This function takes care of ensuring data consistency by checking the Update
 * In Progress (UIP) flag before each read. It also should check the RTC
 * configuration and perform data conversions if necessary (e.g. BCD to binary).
 */
int rtc_read_date(rtc_date *date);

// wrapper function to sys_inb with support to 8-bit unsigned int pointer
void util_sys_inb(int port, uint8_t *byte);
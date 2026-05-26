#pragma once

#include <stdint.h>

/**
 * @brief Structure to hold the date information read from the RTC.
 * @details Contains three fields: `day`, `month`, and `year`, each represented as an 8-bit unsigned integer.
 */
typedef struct {
  uint8_t day;
  uint8_t month;
  uint8_t year;
} rtc_date;

/**
 * @brief Structure to hold the time information read from the RTC.
 * @details Contains three fields: `hours`, `minutes`, and `seconds`, each represented as an 8-bit unsigned integer.
 */
typedef struct {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} rtc_time;

/**
 * @brief Function to read the current date from the RTC and fill the provided `rtc_date` structure.
 * @details This function ensures data consistency by checking the Update In Progress (UIP) flag before reading the date. It also checks the RTC configuration and performs data conversions if necessary (e.g. BCD to binary).
 * @param date Pointer to an `rtc_date` structure that will be filled with the current date read from the RTC.
 * @return Returns 0 on success, non-zero on failure.
 */
int rtc_read_date(rtc_date *date);

/**
 * @brief Function to read the current time from the RTC and fill the provided `rtc_time` structure.
 * @details This function ensures data consistency by checking the Update In Progress (UIP) flag before reading the time. It also checks the RTC configuration to determine if the time is in BCD format and converts it to binary if necessary. Additionally, it handles both 12-hour and 24-hour formats, converting to 24-hour format if needed.
 * @param time Pointer to an `rtc_time` structure that will be filled with the current time read from the RTC.
 * @return Returns 0 on success, non-zero on failure.
 */
int rtc_read_time(rtc_time *time);

/**
 * @brief Utility function to read a byte from a specified I/O port.
 * @details This function is a wrapper around the system call to read from an I/O port. It reads a 32-bit value from the port and then casts it to an 8-bit value, which is stored in the provided byte pointer.
 * @param port The I/O port to read from.
 * @param byte Pointer to a uint8_t variable where the read byte will be stored.
 */
void util_sys_inb(int port, uint8_t *byte);
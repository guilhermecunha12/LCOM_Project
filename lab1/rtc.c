#include "rtc.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>

/** 
 * @brief I/O port used to select which RTC register to read/write(write-only) 
 */
#define RTC_ADDR_REG 0x70

/** 
 * @brief I/O port used to read from or write to the selected RTC register
 */
#define RTC_DATA_REG 0x71

/**
 * @brief RTC Register A: contains the Update-In-Progress (UIP) in bit 7
 */
#define RTC_REG_A 0x0A

/**
 * @brief RTC Register B: contains configuration flags (data format, hour mode, daylight etc.)
 */
#define RTC_REG_B 0x0B

/**
 * @brief RTC Data Register address for seconds (0-59)
 */
#define RTC_REG_SECONDS 0x00

/**
 * @brief RTC Data Register address for minutes (0-59)
 */
#define RTC_REG_MINUTES 0x02

/**
 * @brief RTC register address for hours (0–23 in 24h mode, 1–12 with PM bit in 12h mode)
 */
#define RTC_REG_HOURS 0x04

/**
 * @brief RTC Data Register address for day (1-31)
 */
#define RTC_REG_DAY 0x07

/**
 * @brief RTC Data Register address for month (1-12)
 */
#define RTC_REG_MONTH 0x08

/**
 * @brief RTC Data Register address for year
 */
#define RTC_REG_YEAR 0x09

/**
 * @brief Mask for the Update-In-Progress (UIP) flag in RTC Register A (bit 7). When this bit is set, it indicates that the RTC is currently updating its registers and the data may be inconsistent.
 */
#define RTC_UIP_MSK (1 << 7)

/**
 * @brief Mask for the Data Mode (DM) flag in RTC Register B (bit 2). When this bit is set, the RTC data is in binary format; otherwise, it is in Binary-Coded Decimal (BCD) format.
 */
#define RTC_DM_MSK (1 << 2)

/**
 * @brief Mask for the 24-hour mode flag in RTC Register B (bit 1). When this bit is set, the RTC operates in 24-hour mode; otherwise, it operates in 12-hour mode.
 */
#define RTC_24H_MSK (1 << 1)

/**
 * @brief Utility function to convert a BCD (Binary-Coded Decimal) value to its binary representation.
 * @details The function takes an 8-bit BCD value, extracts the least significant half-byte (LSHB) and the most significant half-byte (MSHB), and computes the equivalent binary value by multiplying the MSHB by 10 and adding the LSHB.
 * @param bcd The BCD value to convert
 * @return The binary representation of the BCD value
 */
static int bcd_to_bin(uint8_t bcd) {
    // lshb -> Least significant half-byte 
    // mshb -> Most significant half-byte
    uint8_t lshb = bcd & 0xF;
    uint8_t mshb = bcd >> 4;
    return mshb * 10 + lshb;
}

/**
 * @brief Helper function to read the day, month, and year from the RTC and store them in the provided pointers.
 * @details This function writes the appropriate register addresses to the RTC address register (0x70) to select the day, month, and year registers, and then reads the corresponding values from the RTC data register (0x71) using the `util_sys_inb` function. The read values are stored in the provided pointers for day, month, and year.
 * @param d Pointer to a uint8_t variable where the day value will be stored.
 * @param m Pointer to a uint8_t variable where the month value will be stored.
 * @param y Pointer to a uint8_t variable where the year value will be stored.
 */
void get_dmy(uint8_t* d, uint8_t* m, uint8_t* y) {
    sys_outb(RTC_ADDR_REG, RTC_REG_DAY);
    util_sys_inb(RTC_DATA_REG, d);
    
    sys_outb(RTC_ADDR_REG, RTC_REG_MONTH);
    util_sys_inb(RTC_DATA_REG, m);

    sys_outb(RTC_ADDR_REG, RTC_REG_YEAR);
    util_sys_inb(RTC_DATA_REG, y);
}

int rtc_read_date(rtc_date *date) {
    uint8_t status;
    sys_outb(RTC_ADDR_REG, RTC_REG_A); // request RTC to write status (register 0x0A) in port 0x71 (data register)
    util_sys_inb(RTC_DATA_REG, &status); // read register with address 0x0A
    while (RTC_UIP_MSK & status) { // while the UIP bit is set, wait and keep reading it until it is 0
        util_sys_inb(RTC_DATA_REG, &status);
        tickdelay(micros_to_ticks(100)); // 100 is enough, probably
    }

    uint8_t days, month, year;
    get_dmy(&days, &month, &year);

    uint8_t info_date;
    sys_outb(RTC_ADDR_REG, RTC_REG_B); // request RTC to write date info in port 0x71
    util_sys_inb(RTC_DATA_REG, &info_date);

    if (!(info_date & RTC_DM_MSK)) { // BCD format
        days = bcd_to_bin(days);
        month = bcd_to_bin(month);
        year = bcd_to_bin(year);
    }

    date->day = days;
    date->month = month;
    date->year = year;

    return 0;
}

/**
 * @brief Helper function to read the hours, minutes, and seconds from the RTC and store them in the provided pointers.
 * @details This function writes the appropriate register addresses to the RTC address register (0x70) to select the seconds, minutes, and hours registers, and then reads the corresponding values from the RTC data register (0x71) using the `util_sys_inb` function. The read values are stored in the provided pointers for hours, minutes, and seconds.
 * @param h Pointer to a uint8_t variable where the hours value will be stored.
 * @param m Pointer to a uint8_t variable where the minutes value will be stored.
 * @param s Pointer to a uint8_t variable where the seconds value will be stored.
 */
void get_hms(uint8_t* h, uint8_t* m, uint8_t* s) {
    sys_outb(RTC_ADDR_REG, RTC_REG_SECONDS);
    util_sys_inb(RTC_DATA_REG, s);
    
    sys_outb(RTC_ADDR_REG, RTC_REG_MINUTES);
    util_sys_inb(RTC_DATA_REG, m);

    sys_outb(RTC_ADDR_REG, RTC_REG_HOURS);
    util_sys_inb(RTC_DATA_REG, h);
}

int rtc_read_time(rtc_time *time) {
    uint8_t status;
    sys_outb(RTC_ADDR_REG, RTC_REG_A); // request RTC to write status
    util_sys_inb(RTC_DATA_REG, &status); // read register with address 0x0A
    while (RTC_UIP_MSK & status) { // while the UIP bit is set, wait and keep reading it until it is 0
        util_sys_inb(RTC_DATA_REG, &status);
        tickdelay(micros_to_ticks(100));
    }

    uint8_t seconds, minutes, hours;
    get_hms(&hours, &minutes, &seconds);

    uint8_t info_date;
    sys_outb(RTC_ADDR_REG, RTC_REG_B); // request RTC to write date info in port 0x71
    util_sys_inb(RTC_DATA_REG, &info_date);

    uint8_t PM_bit = hours & 0x80;
    // Since the hours value will be updated, the PM bit will be erased as we only care for the numeric value of the hours.
    // 92PM in BCD -> 1001 0010 will be converted to 12 PM but the ms bit will be erased
    if (!(info_date & RTC_DM_MSK)) { // BCD format
        seconds = bcd_to_bin(seconds);
        minutes = bcd_to_bin(minutes);
        hours = bcd_to_bin(hours & 0x7F); // removes the most significant bit, which is indicates if it's PM or AM in 12h mode
    }

    if(!(info_date & RTC_24H_MSK)) { // if it's in 12h mode, convert to 24h
        if(PM_bit){ // If PM bit is 1 - true 
            hours = (hours % 12) + 12; // The modulo guarantees that the function is correct when 12PM -> 12:00 in 24hr
        }
        else if (hours == 12){ // To handle the special case of 12AM being midnight
            hours = 0;
        }
        // If the value is in AM the value is kept unchanged
    }
    time->seconds = seconds;
    time->minutes = minutes;
    time->hours = hours;
    return 0;
}


void util_sys_inclb(int port, uint8_t *byte) {
    uint32_t temp;
    sys_inb(port, &temp);
    *byte = (uint8_t)temp;
}
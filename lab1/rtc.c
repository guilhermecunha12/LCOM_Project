#include "rtc.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>

#define TODO return -1

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_SECONDS 0x00
#define RTC_REG_MINUTES 0x02
#define RTC_REG_HOURS 0x04
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)
#define RTC_24H_MSK (1 << 1)

static int bcd_to_bin(uint8_t bcd) {
    uint8_t lsw = bcd & 0xF;
    uint8_t ms  w = bcd >> 4;
    return msw * 10 + lsw;
}

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

void get_hms(uint8_t* h, uint8_t* m, uint8_t* s) {
    sys_outb(RTC_ADDR_REG, RTC_REG_SECONDS);
    util_sys_inb(RTC_DATA_REG, s);
    
    sys_outb(RTC_ADDR_REG, RTC_REG_MINUTES);
    util_sys_inb(RTC_DATA_REG, m);

    sys_outb(RTC_ADDR_REG, RTC_REG_HOURS);
    util_sys_inb(RTC_DATA_REG, h);
}

int rtc_read_time(rtc_time *time) {
    // TODO
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

    if (!(info_date & RTC_DM_MSK)) { // BCD format
        seconds = bcd_to_bin(seconds);
        minutes = bcd_to_bin(minutes);
        hours = bcd_to_bin(hours & 0x7F); // removes the last bit, wich is indicates if it's PM or AM in 12h mode
    }

    if(!(info_date & RTC_24H_MSK)) { // if it's in 12h mode, convert to 24h
        if(hours & 0x80) { // PM
            hours = (hours % 12) + 12;
        } else if (hours == 12) { // if it's 12 AM, set to 0, midnight
            hours = 0;
        }
    }

    time->seconds = seconds;
    time->minutes = minutes;
    time->hours = hours;

    return 0;
}


void util_sys_inb(int port, uint8_t *byte) {
    uint32_t casted_byte;
    sys_inb(port, &casted_byte);
    *byte = (uint8_t)casted_byte;
}
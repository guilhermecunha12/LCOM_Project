#include "rtc.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>

#define TODO return -1

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)

static int bdc_to_bin(uint8_t bcd) { TODO; }

int rtc_read_date(rtc_date *date) {
    sys_outb(RTC_ADDR_REG, RTC_REG_A); // request RTC to write status (register 0x0A) in port 0x71 (data register)
    
    uint8_t status;
    util_sys_inb(RTC_DATA_REG, &status); // read register with address 0x0A
    while (RTC_UIP_MSK & status) { // while the UIP bit is set, wait and keep reading it until it is 0
        util_sys_inb(RTC_DATA_REG, &status);
        tickdelay(micros_to_ticks(100)); // 100 is enough, probably
    }

    TODO;
    // ler uip bit (if ! set, proceed) tickdelay /micro_to_ticks
    // ler DM bit (bit 2) (BCD é por words)
}


void util_sys_inb(int port, uint8_t *byte) {
    uint32_t casted_byte;
    sys_inb(port, &casted_byte);
    *byte = (uint8_t)casted_byte;
}
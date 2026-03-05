#include "bitwise.h"
#include <stdarg.h>

#define TODO return 255

uint8_t clear(uint8_t msk, int pos) { 
    return  msk & ~(0x01 << pos);
 }

uint8_t set(uint8_t msk, int pos) {
    return msk | (0x01 << pos);
}

bool is_set(uint8_t msk, int pos) {
    return msk & (0x01 << pos);
 }

uint8_t lsb(uint16_t wide_msk) { 
    return wide_msk & 0xFF;
 }

uint8_t msb(uint16_t wide_msk) {
    return wide_msk >> 8;
}

uint8_t mask(int pos, ...) { 
    int count = 0;
    va_list args;
    va_start (args,pos);
    uint8_t msk;
    set(msk,pos);
    while(args[count]!=MSK_END){
        set(msk,args[count]);
        count ++;
    }
    return msk;
 }

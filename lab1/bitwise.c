#include "bitwise.h"

#define TODO return 255

uint8_t clear(uint8_t msk, int pos) { 
    uint8_t new_mask = msk & ~(0x01 << pos);
    return new_mask;
 }

uint8_t set(uint8_t msk, int pos) {
    uint8_t set_mask = msk | (0x01 << pos);
    return set_mask;
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
    va_list ap; 

    va_start(ap, pos);

    uint8_t msk = 0x01 << pos;

    int bit = va_arg (ap, int);
    while(bit != MSK_END){
        msk |= (0x01 << bit);
        bit = va_arg (ap, int);
    }

    va_end(ap);
    return msk;
}

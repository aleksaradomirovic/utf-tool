/*
 * SPDX-License-Identifier: 0BSD
 * Copyright (C) 2025 Aleksa Radomirovic
 */

#include "utf.h"

#include <stdbit.h>

#define UTF8_LEAD_MASK 0b11000000
#define UTF8_LEAD_MARK 0b10000000

unsigned int mcharw(const char * mchar) {
    unsigned int lbit = stdc_leading_ones((unsigned char) *mchar);
    if(lbit == 0) return 1;
    if(lbit > 4) return 0;
    return lbit;
}

utf32_t mchar(const char * str, const char ** next) {
    unsigned int width = mcharw(str);
    if(width == 0 || width > 4) return -1;
    
    if(width == 1) {
        if(next != NULL) *next = str + 1;
        return *((const unsigned char *) str);
    }
    
    utf32_t result = 0;
    for(unsigned int i = 0; i < width; i++) {
        unsigned char byte = *((const unsigned char *) str + i);
        if(i > 0) {
            if((byte & UTF8_LEAD_MASK) != UTF8_LEAD_MARK) return -1;
            byte &= ~UTF8_LEAD_MASK;
        } else {
            switch(width) {
                case 2: byte &= 0b00011111; break;
                case 3: byte &= 0b00001111; break;
                case 4: byte &= 0b00000111; break;
            }
        }
        result |= ((utf32_t) byte) << ((width - i - 1) * 6);
    }
    
    if(next != NULL) *next = str + width;
    return result;
}

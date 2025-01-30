/*
 * SPDX-License-Identifier: 0BSD
 * Copyright (C) 2025 Aleksa Radomirovic
 */

#include "utf.h"

#include <stdio.h>
#include <string.h>

static unsigned int wmax = 1;

static void print_str_stats(const char * str) {
    for(const char * c = str; mchar(c, NULL) != '\0';) {
        unsigned int w = mcharw(c);
        if(w > wmax) wmax = w;
        c += w;
    }
    
    unsigned int tabwidth = (wmax * 9);
    
    for(const char * c = str, * n; mchar(c, &n) != '\0'; c = n) {
        printf("%*s%.*s ", tabwidth - 1, "", mcharw(c), c);
    }
    printf("\n");
    
    for(const char * c = str, * n;; c = n) {
        utf32_t i = mchar(c, &n);
        if(i == '\0') break;
        printf("%*sU+%06x ", (unsigned int)(tabwidth - strlen("U+000000")), "", (uint_least32_t) i);
    }
    printf("\n");
    
    for(const char * c = str, * n;; c = n) {
        utf32_t i = mchar(c, &n);
        if(i == '\0') break;

        unsigned int w = mcharw(c);
        printf("%*s", tabwidth - (w * 9) + 1, "");
        for(unsigned int i = 0; i < w; i++) {
            printf("%08b ", (unsigned char) c[i]);
        }
    }
    printf("\n");
}

int main(int argc, char ** argv) {
    for(int i = 1;;) {
        print_str_stats(argv[i]);
        if(++i >= argc) break;
        printf("\n");
    }
    
    return 0;
}

#include "gcc_vr4300/types.h"

#pragma weak memset

// https://en.cppreference.com/w/c/string/byte/memset
void *memset(void *dest, int ch, size_t n) {
    unsigned char *ptr = (unsigned char*)dest;
    size_t i;

    for (i = 0; i < n; i++, ptr++) {
        *ptr = ch;
    }

    return dest;
}

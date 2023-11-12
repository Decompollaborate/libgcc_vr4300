/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(memmove);

// https://en.cppreference.com/w/c/string/byte/memmove
void* memmove(void* dest, const void* src, size_t count) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    size_t i;

    if (dest == src) {
        return dest;
    }

    if (dest < src) {
        for (i = 0; i < count; i ++) {
            *d++ = *s++;
        }
    } else {
        d += count - 1;
        s += count - 1;
        for (i = 0; i < count; i ++) {
            *d-- = *s--;
        }
    }

    return dest;
}

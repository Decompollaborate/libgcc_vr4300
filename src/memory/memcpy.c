/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(memcpy);

// https://en.cppreference.com/w/c/string/byte/memcpy
void* memcpy(void *restrict dest, const void *restrict src, size_t count) {
    unsigned char *restrict d = dest;
    const unsigned char *restrict s = src;
    size_t i;

    for (i = 0; i < count; i ++) {
        *d++ = *s++;
    }

    return dest;
}

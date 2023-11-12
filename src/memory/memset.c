/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(memset);

// https://en.cppreference.com/w/c/string/byte/memset
void *memset(void *dest, int ch, size_t n) {
    unsigned char *ptr = dest;
    size_t i;

    for (i = 0; i < n; i++, ptr++) {
        *ptr = ch;
    }

    return dest;
}

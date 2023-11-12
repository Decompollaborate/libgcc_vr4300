/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(memcmp);

// https://en.cppreference.com/w/c/string/byte/memcmp
int memcmp(const void *lhs, const void *rhs, size_t count) {
    const unsigned char *left = lhs;
    const unsigned char *right = rhs;
    size_t i;

    for (i = 0; i < count; i++, left++, right++) {
        if (*left < *right) {
            return -1;
        }
        if (*left > *right) {
            return 1;
        }
    }

    return 0;
}

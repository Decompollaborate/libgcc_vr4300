/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__fixunssfdi);

/**
 * Gets uint64_t from float32. Negative becomes 0.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__fixunssfdi
 */
uint64_t __fixunssfdi(float32 a) {
    if (a <= 0) {
        return 0;
    }

    register DoubleFloatUnion dull;

    __asm__("trunc.l.s %0, %1" : "=f"(dull.d) : "f"(a));
    return dull.ull;
}

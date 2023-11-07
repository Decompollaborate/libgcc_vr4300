/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__fixunsdfdi);

/**
 * Gets uint64_t from float64. Negative becomes 0.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__fixunsdfdi
 */
uint64_t __fixunsdfdi(float64 a) {
    if (a <= 0) {
        return 0;
    }

    register DoubleFloatUnion dull;

    __asm__("trunc.l.d %0, %1" : "=f"(dull.d) : "f"(a));
    return dull.ull;
}

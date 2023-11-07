/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__powidf2);

/**
 * Raise `a` to the power of `b`
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__powidf2
 */
float64 __powidf2(float64 a, int b) {
    unsigned int n = (b < 0) ? -b : b;
    float64 y = (n % 2 != 0) ? a : 1;

    // Binary exponentiation
    while (n >>= 1) {
        a = a * a;

        if (n % 2 != 0) {
            y = y * a;
        }
    }

    return (b < 0) ? (1 / y) : y;
}

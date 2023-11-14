/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__floatdisf);

/**
 * Gets float32 from int64_t.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__floatdisf
 */
float32 __floatdisf(int64_t i) {
    register Float64Union dull;
    register float32 ret;

    dull.ll = i;
    __asm__("cvt.s.l %0, %1" : "=f"(ret) : "f"(dull.d));
    return ret;
}

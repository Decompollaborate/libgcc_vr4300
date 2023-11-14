/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__floatundidf);

/**
 * Gets float64 from uint64_t.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__floatundidf
 */
float64 __floatundidf(uint64_t i) {
    register Float64Union dull;
    register float64 ret;

    dull.ull = i;
    __asm__("cvt.d.l %0, %1" : "=f"(ret) : "f"(dull.d));
    if ((int64_t)i < 0) {
        // cvt.d.l assumes signed input, adjust output
        ret += 18446744073709551616.0; // 2^64
    }

    return ret;
}

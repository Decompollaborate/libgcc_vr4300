/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

#if ABI_N32 || ABI_N64
EXPORT(__floatsitf);

/**
 * Gets float64 from int64_t.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__floatsitf
 */
float128 __floatsitf(int32_t i) {
    Float128Union ret;
    int32_t sign = 0;
    int32_t exponent;
    uint32_t value;

    ret.hex.upper = 0;
    ret.hex.lower = 0;

    if (i == 0) {
        return 0;
    }

    if (i < 0) {
        sign = 1;
        i = (~i) + 1;
    }
    value = i;

    exponent = -1;
    while (value > 0) {
        exponent++;
        value = value >> 1;
    }

    // set sign
    ret.hex.upper |= ((uint64_t)sign) << 63;

    // hide the leading bit
    i &= ~(1 << exponent);

    // set the biased exponent
    ret.hex.upper |= ((uint64_t)(exponent + 0x3FFF)) << 48;

    // set the mantissa
    ret.hex.upper |= ((uint64_t)i) << (48 - exponent);

    return ret.ld;
}
#endif

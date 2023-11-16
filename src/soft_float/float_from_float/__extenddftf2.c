/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

#if ABI_N32 || ABI_N64
EXPORT(__extenddftf2);

/**
 * Gets float128 from float64.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__extenddftf2
 */
float128 __extenddftf2(float64 a) {
    // IEEE754 128-bit floats are encoded in 128 bits as follows:
    // Sign bit: 1 bit (bit 127)
    // Encoded exponent: 15 bits (bits 112 ~ 126)
    // Fraction/Mantissa: 112 bits (bits 0 ~ 111)

    Float128Union ret;
    Float64Union arg;

    int32_t sign;
    int32_t encodedExponent;
    int32_t realExponent;
    bool mantissaIsZero;

    arg.d = a;

    ret.hex.upper = 0;
    ret.hex.lower = 0;

    sign = arg.ull >> 63;

    // If parameter is zero, then return zero
    if ((arg.ull & ~(1ULL << 63)) == 0) {
        // Preserve the sign
        ret.hex.upper |= arg.ull & (1ULL << 63);
        return ret.ld;
    }

    // Clear up the sign
    arg.ull &= ~(1ULL << 63);

    encodedExponent = arg.ull >> 52;
    // Clear up the encoded exponent
    arg.ull &= ~0x7FF0000000000000ULL;

    // Exponent bias: 0x3FF
    realExponent = encodedExponent - 0x3FF;

    mantissaIsZero = (arg.ull == 0);

    if (encodedExponent == 0) {
        // subnormals

        ret.hex.upper |= ((uint64_t)sign) << 63;
        // no need to set the exponent part since it was already zero'd

        // Set the mantissa
        ret.hex.upper |= arg.ull >> (52 - 48);
        ret.hex.lower |= arg.ull << (64 - (52 - 48));

        return ret.ld;
    }

    if (encodedExponent == 0x7FF) {
        // Infinity and NaN

        ret.hex.upper |= ((uint64_t)sign) << 63;
        ret.hex.upper |= 0x7FFF000000000000ULL;

        if (!mantissaIsZero) {
            // NaN

            // Set the mantissa to any non-zero value
            ret.hex.lower |= 0xA1F << 16;
            ret.hex.lower |= 0x4300;
        }

        return ret.ld;
    }

    ret.hex.upper |= ((uint64_t)sign) << 63;

    // re-encode the exponent
    ret.hex.upper |= ((uint64_t)(realExponent + 0x3FFF)) << 48;

    // Set the mantissa
    ret.hex.upper |= arg.ull >> (52 - 48);
    ret.hex.lower |= arg.ull << (64 - (52 - 48));

    return ret.ld;
}
#endif

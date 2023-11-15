/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

#if ABI_N32 || ABI_N64
EXPORT(__fixtfsi);

/**
 * Gets int32_t from float128.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__fixtfsi
 */
int32_t __fixtfsi(float128 a) {
    // IEEE754 128-bit floats are encoded in 128 bits as follows:
    // Sign bit: 1 bit (bit 127)
    // Encoded exponent: 15 bits (bits 112 ~ 126)
    // Fraction/Mantissa: 112 bits (bits 0 ~ 111)

    Float128Union flt;
    int32_t sign;
    int32_t encodedExponent;
    int32_t realExponent;
    bool mantissaIsZero;
    int32_t computedValue;

    uint32_t truncantedMantissa;

    flt.ld = a;

    // If parameter is zero (or negative zero), then return zero
    if (flt.hex.lower == 0) {
        if ((flt.hex.upper == 0) || (flt.hex.upper & (1ULL << 63))) {
            return 0;
        }
    }

    sign = flt.hex.upper >> 63;
    // Clear up the sign
    flt.hex.upper &= ~(1ULL << 63);

    encodedExponent = flt.hex.upper >> 48;
    // Clear up the encoded exponent
    flt.hex.upper &= ~0x7FFF000000000000ULL;

    // Exponent bias: 0x3FFF
    realExponent = encodedExponent - 0x3FFF;

    mantissaIsZero = (flt.hex.upper == 0) && (flt.hex.lower == 0);

    if (encodedExponent == 0) {
        // subnormals
        return 0;
    }

    if (encodedExponent == 0x7FFF) {
        // Infinity and NaN

        if (mantissaIsZero) {
            // Infinity, return max int

            // TODO: should this be handled in any other way?

            if (sign) {
                return INT32_MIN;
            } else {
                return INT32_MAX;
            }
        }

        // NaN
        return 0; // ?
    }

    // TODO: Figure out proper way to handle values outside of the int32_t range

    if (realExponent < 0) {
        // Value smaller than 1, truncate to zero (?)
        return 0;
    }

    if (realExponent > 31) {
        // Value is larger than int32_t, return int max

        // TODO: should this be handled in any other way?

        if (sign) {
            return INT32_MIN;
        } else {
            return INT32_MAX;
        }
    }

    if (mantissaIsZero) {
        // If the mantissa is zero, just shift 1 by the exponent to get the value
        computedValue = 1 << realExponent;

        if (sign) {
            computedValue *= -1;
        }

        return computedValue;
    }

    // We truncate the mantissa from 112 bits to 32 bits because an `int32_t` can't fit more than that
    truncantedMantissa = flt.hex.upper >> 16;

    // Manually compute the value
    // The following algorithm only works for converting a float that is greater or equal than 1 but smaller than INT_MAX

    // The implicit leading bit
    computedValue = 1;

    while (realExponent-- > 0) {
        computedValue *= 2;

        // Iterate the mantissa, from the upper bits to the lowest ones
        if (truncantedMantissa & 0x80000000) {
            computedValue += 1;
        }
        truncantedMantissa <<= 1;
    }

    if (sign) {
        computedValue *= -1;
    }

    return computedValue;
}
#endif

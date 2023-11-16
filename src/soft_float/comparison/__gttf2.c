/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

#if ABI_N32 || ABI_N64
EXPORT(__gttf2);

/**
 * Return non-zero if `a` is strictly greater than `b`
 *
 * ret = a > b;
 *
 * If either argument is NaN then TODO
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__gttf2
 */
fcmp __gttf2(float128 a, float128 b) {
    Float128Union argA = { .ld = a };
    Float128Union argB = { .ld = b };
    int32_t signA;
    int32_t signB;
    int32_t encodedExponentA;
    int32_t encodedExponentB;
    bool mantissaAIsZero;
    bool mantissaBIsZero;

    signA = argA.hex.upper >> 63;
    // Clear up the sign
    argA.hex.upper &= ~(1ULL << 63);

    signB = argB.hex.upper >> 63;
    // Clear up the sign
    argB.hex.upper &= ~(1ULL << 63);

    encodedExponentA = argA.hex.upper >> 48;
    // Clear up the encoded exponent
    argA.hex.upper &= ~0x7FFF000000000000ULL;

    encodedExponentB = argB.hex.upper >> 48;
    // Clear up the encoded exponent
    argB.hex.upper &= ~0x7FFF000000000000ULL;

    mantissaAIsZero = (argA.hex.upper == 0) && (argA.hex.lower == 0);
    mantissaBIsZero = (argB.hex.upper == 0) && (argB.hex.lower == 0);

    // normalize the sign if the argument is zero
    if ((encodedExponentA == 0) && mantissaAIsZero) {
        signA = 0;
    }
    if ((encodedExponentB == 0) && mantissaBIsZero) {
        signB = 0;
    }

    if ((encodedExponentA == 0x7FFF)) {
        // argA is either Infinity or NaN
        if (!mantissaAIsZero) {
            // argA is NaN
            Fpcsr_SetCause_InvalidOperation();
        }
    }

    if ((encodedExponentB == 0x7FFF)) {
        // argB is either Infinity or NaN

        if (!mantissaBIsZero) {
            // argB is NaN
            Fpcsr_SetCause_InvalidOperation();
        }
    }

    // First check by the sign
    if (signA != signB) {
        if (!signA) {
            // argA is positive
            if (signB) {
                // argB is negative
                return 1;
            }
        }
        return 0;
    }

    // From now on, signs are the same

    if (signA == 0) {
        if ((encodedExponentA == 0) && (encodedExponentB == 0)) {
            if (mantissaAIsZero && mantissaBIsZero) {
                // both are zero
                return 0;
            }
        }
    }


    if ((encodedExponentB == 0x7FFF)) {
        if (!signB) {
            // argB is +infinity
            return 0;
        }
    }

    if ((encodedExponentA == 0x7FFF)) {
        if (signA) {
            // argA is -infinity
            return 0;
        }

        // argA is +infinity
        return 1;
    }

    if (encodedExponentA > encodedExponentB) {
        // The exponent of A is greater
        return 1;
    }
    if (encodedExponentB > encodedExponentA) {
        // The exponent of B is greater
        return 0;
    }

    // Both exponents are the same

    // TODO

    __asm__("break;");
}
#endif

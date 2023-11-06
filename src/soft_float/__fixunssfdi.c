#include "gcc_vr4300/types.h"

#pragma weak __fixunssfdi

/**
 * Converts single float to uint64_t. Negative becomes 0
 */

// https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__fixunssfdi
uint64_t __fixunssfdi(float a) {
    if (a <= 0.0f) {
        return 0;
    }

    register union {
        double d;
        uint64_t ull;
    } dull;

    __asm__("cvt.l.s %0, %1" : "=f"(dull.d) : "f"(a));
    return dull.ull;
}

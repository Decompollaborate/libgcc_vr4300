#include "gcc_vr4300/types.h"

#pragma weak __fixdfdi

/**
 * Gets int64_t from float64.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__fixdfdi
 */
int64_t __fixdfdi(float64 a) {
    register DoubleFloatUnion dull;

    __asm__("cvt.l.d %0, %1" : "=f"(dull.d) : "f"(a));
    return dull.ll;
}

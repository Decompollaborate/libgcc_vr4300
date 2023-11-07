#include "gcc_vr4300/types.h"

#pragma weak __fixsfdi

/**
 * Gets int64_t from float32.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__fixsfdi
 */
int64_t __fixsfdi(float32 a) {
    register DoubleFloatUnion dull;

    __asm__("trunc.l.s %0, %1" : "=f"(dull.d) : "f"(a));
    return dull.ll;
}

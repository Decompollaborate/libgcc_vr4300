#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__powisf2);

/**
 * Raise `a` to the power of `b`
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__powisf2
 */
float32 __powisf2(float32 a, int b) {
    unsigned int n = (b < 0) ? -b : b;
    float32 y = (n % 2 != 0) ? a : 1;

    // Binary exponentiation
    while (n >>= 1) {
        a = a * a;

        if (n % 2 != 0) {
            y = y * a;
        }
    }

    return (b < 0) ? (1 / y) : y;
}

#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__floatundisf);

/**
 * Gets float32 from uint64_t.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__floatundisf
 */
float32 __floatundisf(uint64_t i) {
    register DoubleFloatUnion dull;
    register float32 ret;

    dull.ull = i;
    __asm__("cvt.s.l %0, %1" : "=f"(ret) : "f"(dull.d));
    if ((int64_t)i < 0) {
        // cvt.s.l assumes signed input, adjust output
        ret += 4294967296.0f; // 2^32
    }

    return ret;
}

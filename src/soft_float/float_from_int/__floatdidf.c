#include "gcc_vr4300/types.h"
#include "gcc_vr4300/export.h"

EXPORT(__floatdidf);

/**
 * Gets float64 from int64_t.
 *
 * https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html#c.__floatdidf
 */
float64 __floatdidf(int64_t i) {
    register DoubleFloatUnion dull;
    register float64 ret;

    dull.ll = i;
    __asm__("cvt.d.l %0, %1" : "=f"(ret) : "f"(dull.d));
    return ret;
}

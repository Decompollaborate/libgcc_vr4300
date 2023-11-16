#ifndef GCC_VR4300_SOFT_FLOAT_H
#define GCC_VR4300_SOFT_FLOAT_H

#include "types.h"

static inline bool Fpcsr_IsEnabled_InvalidOperation(void) {
    uint32_t fpcsr;

    __asm__("cfc1 %0, $31" : "=r"(fpcsr));

    return (fpcsr & (1 << 11)) ? 1 : 0;
}

/**
 * Set the "Invalid operation" exception.
 *
 * If the "Enable bit" for this exception is turned on then the hardware will
 * trigger the exception by itself.
 */
static inline void Fpcsr_SetCause_InvalidOperation(void) {
    uint32_t fpcsr;

    __asm__("cfc1 %0, $31" : "=r"(fpcsr));

    fpcsr |= (1 << 11);

    __asm__("ctc1 %0, $31" : : "r"(fpcsr));
}

#endif

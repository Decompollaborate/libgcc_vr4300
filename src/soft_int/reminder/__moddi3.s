/* SPDX-FileCopyrightText: © 2023 Decompollaborate */
/* SPDX-License-Identifier: MIT */

#include "gcc_vr4300/hasm.h"

.section .text, "ax"

.set push

.set noreorder
.set gp=64

/**
  Returns the reminder between two int64_t numbers

  Equivalent to this C code

int64_t __moddi3(int64_t numerator, int64_t denominator) {
    return numerator % denominator;
}
 */

// https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-integer-arithmetic.html#_CPPv49__moddi3mm
LEAF(__moddi3)
#if ABI_O32 || ABI_EABI32

ASM_STACK_START

// store numerator pair into stack
sw          $a0, 0x0($sp)
sw          $a1, 0x4($sp)

// store denominator pair into stack
sw          $a2, 0x8($sp)
sw          $a3, 0xC($sp)

// load denominator
ld          $t1, 0x8($sp)

// load numerator
ld          $t0, 0x0($sp)

// get the reminder into $v0
drem        $v0, $t0, $t1

// set $v1 to the lower 32 bits of the reminder
dsll32      $v1, $v0, 0
dsra32      $v1, $v1, 0

ASM_STACK_END

// set $v0 to the upper 32 bits of the reminder
jr          $ra
 dsra32     $v0, $v0, 0

#elif ABI_N32 || ABI_O64 || ABI_N64 || ABI_EABI64

// get the reminder into $v0
drem        $v0, $a0, $a1

jr          $ra
 nop

#else

#error "Unsupported ABI detected"

#endif
END(__moddi3)

.set pop

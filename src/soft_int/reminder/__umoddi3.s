#include "gcc_vr4300/hasm.h"

.section .text, "ax"

.set push

.set noreorder
.set gp=64

/**
  Returns the reminder between two uint64_t numbers

  Equivalent to this C code

uint64_t __umoddi3(uint64_t numerator, uint64_t denominator) {
    return numerator % denominator;
}
 */

// https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-integer-arithmetic.html#_CPPv49__umoddi3mm
LEAF(__umoddi3)
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

// get the reminder into $v0 (unsigned)
dremu       $v0, $t0, $t1

// set $v1 to the lower 32 bits of the reminder
dsll32      $v1, $v0, 0
dsra32      $v1, $v1, 0

// set $v0 to the upper 32 bits of the reminder
jr          $ra
 dsra32     $v0, $v0, 0
END(__umoddi3)

.set pop

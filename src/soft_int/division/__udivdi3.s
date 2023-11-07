#include "gcc_vr4300/hasm.h"

.section .text, "ax"

.set push

.set noreorder
.set gp=64

/**
  Returns the quotient between two uint64_t numbers

  Equivalent to this C code

uint64_t __udivdi3(uint64_t numerator, uint64_t denominator) {
    return numerator / denominator;
}
 */

// https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-integer-arithmetic.html#_CPPv49__udivdi3mm
LEAF(__udivdi3)
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

// get the quotient into $v0 (unsigned)
ddivu       $v0, $t0, $t1

// set $v1 to the lower 32 bits of the quotient
dsll32      $v1, $v0, 0
dsra32      $v1, $v1, 0

// set $v0 to the upper 32 bits of the quotient
jr          $ra
 dsra32     $v0, $v0, 0
END(__udivdi3)

.set pop

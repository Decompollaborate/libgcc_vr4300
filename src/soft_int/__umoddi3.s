#include "gcc_vr4300/hasm.h"

.section .text, "ax"

.set push

.set noreorder
.set gp=64

/**
  Equivalent to this C code

uint64_t __ull_rem(uint64_t numerator, uint64_t denominator) {
    return numerator % denominator;
}
 */

LEAF(__umoddi3)
// store numerator pair into stack
sw          $a0, 0x0($sp)
sw          $a1, 0x4($sp)

// store denominator pair into stack
sw          $a2, 0x8($sp)
sw          $a3, 0xC($sp)

// load denominator
ld          $t7, 0x8($sp)

// load numerator
ld          $t6, 0x0($sp)

// check for zero division
bnez        $t7, .Lfinish

// set quotient into LO and reminder into HI
 ddivu      $zero, $t6, $t7

// zero division
break       7

.Lfinish:

// get the reminder
mfhi        $v0

// set $v1 to the lower 32 bits of the reminder
dsll32      $v1, $v0, 0
dsra32      $v1, $v1, 0

// set $v0 to the upper 32 bits of the reminder
jr          $ra
 dsra32     $v0, $v0, 0
END(__umoddi3)

.set pop

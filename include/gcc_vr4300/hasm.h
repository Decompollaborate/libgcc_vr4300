#ifndef GCC_VR4300_HASM_H
#define GCC_VR4300_HASM_H

#include "version.h"
#include "abi.h"

#define LEAF(x) \
    .align 2 ;\
    .globl x ;\
    .type x, @function ;\
    .weak x ;\
    .symver x, x @@ LIBGCC_VR4300_SYMVER ;\
    x: ;\
        .ent x, 0 ;\
        .frame $sp, 0, $ra

#define END(x) \
    .size x, . - x ;\
    .end x; \
    .ident "libgcc_vr4300 " LIBGCC_VR4300_VER_STRING; \
    .ident "https://github.com/Decompollaborate/libgcc_vr4300"

#if ABI_EABI32
#define ASM_STACK_START addiu $sp, $sp, -0x10
#define ASM_STACK_END   addiu $sp, $sp,  0x10
#else
#define ASM_STACK_START
#define ASM_STACK_END
#endif

#endif

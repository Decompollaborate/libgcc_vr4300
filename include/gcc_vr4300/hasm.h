#ifndef GCC_VR4300_H
#define GCC_VR4300_H

#include "version.h"

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

#endif

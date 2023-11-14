#ifndef GCC_VR4300_TYPES_H
#define GCC_VR4300_TYPES_H

#include "macro.h"

typedef __SIZE_TYPE__ size_t;

typedef __INT64_TYPE__ int64_t;
STATIC_ASSERT(sizeof(int64_t) == 8, "int64_t type's size is not 8");

typedef __UINT64_TYPE__ uint64_t;
STATIC_ASSERT(sizeof(uint64_t) == 8, "uint64_t type's size is not 8");


typedef float float32;
STATIC_ASSERT(sizeof(float32) == 4, "float32 type's size is not 4");

typedef double float64;
STATIC_ASSERT(sizeof(float64) == 8, "float64 type's size is not 8");

#if _MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64
typedef long double float128;
STATIC_ASSERT(sizeof(float128) == 16, "float128 type's size is not 16");
#endif

typedef int fcmp __attribute__ ((mode (__libgcc_cmp_return__)));

typedef union DoubleFloatUnion {
    float64 d;
    int64_t ll;
    uint64_t ull;
} DoubleFloatUnion;

#endif

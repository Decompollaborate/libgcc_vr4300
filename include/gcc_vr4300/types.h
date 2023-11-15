#ifndef GCC_VR4300_TYPES_H
#define GCC_VR4300_TYPES_H

#include "macro.h"
#include "abi.h"

#if __STDC_VERSION__ >= 202311L
// do nothing
#else
typedef _Bool bool;
#endif

typedef __SIZE_TYPE__ size_t;

typedef __INT32_TYPE__ int32_t;
STATIC_ASSERT(sizeof(int32_t) == 4, "int32_t type's size is not 4");

typedef __UINT32_TYPE__ uint32_t;
STATIC_ASSERT(sizeof(uint32_t) == 4, "uint32_t type's size is not 4");

typedef __INT64_TYPE__ int64_t;
STATIC_ASSERT(sizeof(int64_t) == 8, "int64_t type's size is not 8");

typedef __UINT64_TYPE__ uint64_t;
STATIC_ASSERT(sizeof(uint64_t) == 8, "uint64_t type's size is not 8");


typedef float float32;
STATIC_ASSERT(sizeof(float32) == 4, "float32 type's size is not 4");

typedef double float64;
STATIC_ASSERT(sizeof(float64) == 8, "float64 type's size is not 8");

#if ABI_N32 || ABI_N64
typedef long double float128;
STATIC_ASSERT(sizeof(float128) == 16, "float128 type's size is not 16");
#endif

typedef int fcmp __attribute__ ((mode (__libgcc_cmp_return__)));


#define INT32_MAX ((int32_t)0x7FFFFFFF)
#define INT32_MIN ((int32_t)0x80000000)


typedef union Float64Union {
    float64 d;
    int64_t ll;
    uint64_t ull;
} Float64Union;

#if ABI_N32 || ABI_N64
typedef union Float128Union {
    float128 ld;
    struct {
        uint64_t upper;
        uint64_t lower;
    } hex;
} Float128Union;
STATIC_ASSERT(sizeof(Float128Union) == 16, "Float128Union type's size is not 16");
#endif

#endif

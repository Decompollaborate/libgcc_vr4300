#ifndef GCC_VR4300_TYPES_H
#define GCC_VR4300_TYPES_H

typedef __SIZE_TYPE__ size_t;

typedef __INT64_TYPE__ int64_t;
typedef __UINT64_TYPE__ uint64_t;

typedef float float32;
typedef double float64;

typedef union DoubleFloatUnion {
    float64 d;
    int64_t ll;
    uint64_t ull;
} DoubleFloatUnion;

#endif

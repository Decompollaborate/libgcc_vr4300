#ifndef GCC_VR4300_H
#define GCC_VR4300_H

// TODO: header guards
typedef unsigned int size_t;

typedef signed long long int64_t;
typedef unsigned long long uint64_t;

typedef float float32;
typedef double float64;

typedef union DoubleFloatUnion {
    float64 d;
    int64_t ll;
    uint64_t ull;
} DoubleFloatUnion;

#endif

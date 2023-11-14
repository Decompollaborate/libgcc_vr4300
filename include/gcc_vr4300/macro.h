#ifndef GCC_VR4300_MACRO_H
#define GCC_VR4300_MACRO_H


#if __STDC_VERSION__ >= 202311L
// C23

// https://en.cppreference.com/w/c/language/_Static_assert
#define STATIC_ASSERT(expression, message) static_assert(expression, message)

#elif __STDC_VERSION__ >= 201112L
// C11

#define STATIC_ASSERT(expression, message) _Static_assert(expression, message)

#else

#define STATIC_ASSERT(expression, message)

#endif


#endif

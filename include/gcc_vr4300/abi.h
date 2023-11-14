#ifndef GCC_VR4300_ABI_H
#define GCC_VR4300_ABI_H

#if (defined(_MIPS_SIM) && (_MIPS_SIM == _ABIO32))
#define ABI_O32         1
#else
#define ABI_O32         0
#endif

#if (defined(_MIPS_SIM) && (_MIPS_SIM == _ABIN32))
#define ABI_N32         1
#else
#define ABI_N32         0
#endif

#if (defined(_MIPS_SIM) && (_MIPS_SIM == _ABIO64))
#define ABI_O64         1
#else
#define ABI_O64         0
#endif

#if (defined(_MIPS_SIM) && (_MIPS_SIM == _ABI64))
#define ABI_N64         1
#else
#define ABI_N64         0
#endif

#if (defined(__mips_eabi) && __mips_eabi && !defined(__mips64))
#define ABI_EABI32      1
#else
#define ABI_EABI32      0
#endif

#if (defined(__mips_eabi) && __mips_eabi && defined(__mips64) && __mips64)
#define ABI_EABI64      1
#else
#define ABI_EABI64      0
#endif

#endif

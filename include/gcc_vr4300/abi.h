#ifndef GCC_VR4300_ABI_H
#define GCC_VR4300_ABI_H

#define ABI_O32        (defined(_MIPS_SIM) && (_MIPS_SIM == _ABIO32))
#define ABI_N32        (defined(_MIPS_SIM) && (_MIPS_SIM == _ABIN32))
#define ABI_O64        (defined(_MIPS_SIM) && (_MIPS_SIM == _ABIO64))
#define ABI_N64        (defined(_MIPS_SIM) && (_MIPS_SIM == _ABI64))
#define ABI_EABI32     (defined(__mips_eabi) && __mips_eabi && !defined(__mips64))
#define ABI_EABI64     (defined(__mips_eabi) && __mips_eabi && defined(__mips64) && __mips64)

#endif

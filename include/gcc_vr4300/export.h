#ifndef GCC_VR4300_EXPORT_H
#define GCC_VR4300_EXPORT_H

#include "version.h"

// Mark the symbol as weak and add version spam
#define EXPORT(name) \
    __asm__(".weak " #name); \
    __asm__(".symver " #name ", " #name " @@LIBGCC_VR4300_" LIBGCC_VR4300_VER_STRING); \
    __asm__(".ident \"libgcc_vr4300 " LIBGCC_VR4300_VER_STRING "\""); \
    __asm__(".ident \"https://github.com/Decompollaborate/libgcc_vr4300\"")

#endif

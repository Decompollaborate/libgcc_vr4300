#ifndef GCC_VR4300_VERSION_H
#define GCC_VR4300_VERSION_H

#define LIBGCC_VR4300_VER_MAJOR 1
#define LIBGCC_VR4300_VER_MINOR 0
#define LIBGCC_VR4300_VER_PATCH 0

#define _STRINGIFY2(x) #x
#define _STRINGIFY(x) _STRINGIFY2(x)
#define _CONCAT2(x, y) x ## y
#define _CONCAT(x, y) _CONCAT2(x, y)

#define LIBGCC_VR4300_VER_STRING "v" _STRINGIFY(LIBGCC_VR4300_VER_MAJOR) "." _STRINGIFY(LIBGCC_VR4300_VER_MINOR) "." _STRINGIFY(LIBGCC_VR4300_VER_PATCH)

#define LIBGCC_VR4300_SYMVER _CONCAT(_CONCAT(_CONCAT(LIBGCC_VR4300_v, LIBGCC_VR4300_VER_MAJOR), _CONCAT(., LIBGCC_VR4300_VER_MINOR)), _CONCAT(., LIBGCC_VR4300_VER_PATCH))

#endif

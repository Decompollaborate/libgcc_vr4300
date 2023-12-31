# libgcc_vr4300

A subset of `libgcc`, targetting the MIPS VR4300 CPU.

## What is this?

This repository provides various functions of `libgcc`, targetting specifically
the MIPS VR4300 CPU (the one used by the Nintendo 64).

This library is meant to be used with MIPS GCC toolchains that do not provide
their own `libgcc`.

## What is `libgcc`?

`libgcc` is a runtime library provided by GCC. This library contains functions
used by GCC "whenever it needs to perform some operation that is too
complicated to emit inline code for"
(<https://gcc.gnu.org/onlinedocs/gccint/Libgcc.html>). There's no way to tell
GCC to emit instructions for those operations instead of using functions from
`libgcc`.

Most functions from `libgcc` are software based instructions for performing
integer and float arithmetic that the target architecture can't process
directly.

GCC can also emit implicit calls to standard C functions like `memcmp` or
`memset`. Said functions are not part of an official `libgcc`.

## Features

This library was made to be used with N64 decompilation projects that want to
support building with modern GCC toolchains, this means not every function from
an official `libgcc` library are implemented, only the ones that have been
required by the tested games.

- `libgcc` implemented functions:
  - Software floating point emulation functions.
    - Float from integer conversion: `__floatdidf`, `__floatdisf`,
      `__floatundidf`, `__floatundisf`.
    - Integer from float conversion: `__fixdfdi`, `__fixsfdi`, `__fixunsdfdi`.
      `__fixunssfdi`.
    - Miscellaneous float operations: `__powidf2`, `__powisf2`.
  - Integer arithmetic functions.
    - Division operations: `__divdi3`, `__udivdi3`.
    - Reminder operations: `__moddi3`, `__umoddi3`.
- `libc` implemented functions:
  - This library also provides some `libc` functiosn because GCC is able to
    emit them implicitly.
  - Memory functions: `memcmp`, `memset`, `memcpy`, `memmove`.
- Linking this as a library to a project allows the linker to only link the
  functions that the project actually uses, contrary to simply linking all the
  functions and wasting precious space.
- All the functions provided by this library are marked as `weak` functions in
  the case the user provides their own implementations for some of the
  functions of this library and wants to use those instead.
- Compatible with various ABIs: `o32`, `n32`, `o64`, `n64`, `eabi32` and
  `eabi64`.

## Why I made this?

I think it is very annoying that every decompilation repository that wants to
have support for a modern GCC toolchain may require copying a file that
implements the required functions again and again. Some of those repositories
may add new features to that file or fix bugs, but those changes won't went
spreaded automatically to the other repositories.

Because of this I decided to make this library, with the idea of every new
addition and fix to be placed on a centralized place that everybody can use.
Just wire up the makefile to download the prebuilt libraries and link them
and you are done!

## Download

This repository provides prebuilt binaries in the
[releases](https://github.com/Decompollaborate/libgcc_vr4300/releases) page.

If you want a direct link for the latest version of a specific ABI access
<https://github.com/Decompollaborate/libgcc_vr4300/releases/latest/download/libgcc_vr4300-ABI.tar.gz>
and replace `ABI` with your desired ABI. For example, the download link of the
`o32` ABI is the following:
<https://github.com/Decompollaborate/libgcc_vr4300/releases/latest/download/libgcc_vr4300-o32.tar.gz>.
This link will always point to the latest version without needing to change it.

## Building

### Dependencies

There are a few build dependencies to build this library locally:

- `build-essential`
- `gcc-mips-linux-gnu` (or any other GCC MIPS cross compiler)

To install those dependencies on a Debian/Ubuntu-like distro:

```bash
apt install build-essential gcc-mips-linux-gnu
```

### Local building

After cloning the repository, run the following command.

```bash
make TARGET_ABI=ABI
```

Change `ABI` to the desired ABI to build. The supported values for `ABI` are
`o32`, `n32`, `o64`, `n64`, `eabi32` and `eabi64`.

To use a different GCC cross compiler, pass `CROSS=` with the prefix of the
toolchain. For example `CROSS=mips-linux-gnu-`.

The built library will be placed on `build/ABI/libgcc_vr4300.a`, where `ABI` is
the ABI passed to the `make` command.

## References

- <https://en.cppreference.com/w/c/string/byte/memcmp>
- <https://en.cppreference.com/w/c/string/byte/memset>
- <https://en.cppreference.com/w/c/string/byte/memcpy>
- <https://en.cppreference.com/w/c/string/byte/memmove>
- <https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-floating-point-emulation.html>
- <https://gcc.gnu.org/onlinedocs/gccint/Soft-float-library-routines.html>
- <https://gcc.gnu.org/onlinedocs/gccint/the-gcc-low-level-runtime-library/routines-for-integer-arithmetic.html>

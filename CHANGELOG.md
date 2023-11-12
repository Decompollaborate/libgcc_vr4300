# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- `libc` functions:
  - Memory functions: `memcpy`, `memmove`.

## [v0.1.0] - 2023-11-07

### Added

- First release!
- `libgcc` functions:
  - Software floating point emulation functions.
    - Float from integer conversion: `__floatdidf`, `__floatdisf`,
      `__floatundidf`, `__floatundisf`.
    - Integer from float conversion: `__fixdfdi`, `__fixsfdi`, `__fixunsdfdi`.
      `__fixunssfdi`.
    - Miscellaneous float operations: `__powidf2`, `__powisf2`.
  - Integer arithmetic functions.
    - Division operations: `__divdi3`, `__udivdi3`.
    - Reminder operations: `__moddi3`, `__umoddi3`.
- `libc` functions:
  - This library also provides some `libc` functiosn because GCC is able to
    emit them implicitly.
  - Memory functions: `memcmp`, `memset`.
- All the functions provided by this library are marked as `weak` functions in
  the case the user provides their own implementations for some of the
  functions of this library and wants to use those instead.
- Compatible with various ABIs: `o32`, `n32`, `o64`, `n64`.

[unreleased]: https://github.com/Decompollaborate/spimdisasm/compare/v0.1.0...HEAD
[v0.1.0]: https://github.com/Decompollaborate/spimdisasm/releases/tag/v0.1.0

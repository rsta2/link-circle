Ableton Link support for Circle
===============================

Overview
--------

This is an attempt to add Ableton Link support to [Circle](https://github.com/rsta2/circle). Because Ableton Link uses the [Asio C++ library](https://github.com/chriskohlhoff/asio), which requires many functions of the C and C++ standard libraries and POSIX-like operating system and network support, the [circle-stdlib project](https://codeberg.org/larchcone/circle-stdlib) is used instead of standalone Circle. circle-stdlib is making progress in POSIX-like network support too.

This can be discussed [here](https://github.com/rsta2/circle/issues/560).

Using
-----

As a preliminary this assumes, that you have git and the necessary toolchains already installed. You can download the source code using:

```
git clone https://github.com/rsta2/link.git
cd link
make submodules
```

Currently the circle-newlib submodule has to be patched with:

```
make patch
```

Then configure and build circle-stdlib and the linkhut tool in examples/linkhut/ (for Raspberry Pi 3 64-bit):

```
./configure -r 3 -p aarch64-none-elf-
make -j
```

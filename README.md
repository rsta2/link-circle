link-circle
===========

Overview
--------

This project provides help for adding [Ableton Link](https://www.ableton.com/en/link) support to [Circle](https://github.com/rsta2/circle) applications. Beside the [Link cross-platform source code library](https://github.com/Ableton/link) it includes the [circle-stdlib project](https://codeberg.org/larchcone/circle-stdlib) as a submodule. circle-stdlib provides most of the software interfaces, which are necessary to build Ableton Link for Circle. This project contains some examples, ported from the Link cross-platform source code library, which demonstrate, how a Circle program is build, which includes Ableton Link support.

Status
------

This is currently based on Ableton Link 3.1.5. As far it was possible to test it, the Linkhut tool and an extended port of the ESP32 example (metro) are working. Also most of the Link core unit tests are working. Some of the tests cannot be build, because *serial_io* module is not available.

Building
--------

You need to install a bare-metal toolchain from [here](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). The build has been tested on a Linux host with GCC version *15.2.Rel1* from this website.

You can download the link-circle source code and the necessary submodules using:

```
git clone https://github.com/rsta2/link-circle.git
cd link-circle
make submodules
```

Then configure and build circle-stdlib (here for Raspberry Pi 3 64-bit). The `-p` option must be applied with an absolute path to the toolchain binaries, if they are not in the `PATH` environment variable.

```
./configure -r 3 -p aarch64-none-elf-
make -j
```

Now you can go to an example or test directory and build it, e.g.:

```
cd examples/linkhut
make -j
```

Cleanup project with:

```
make clean
```

Credits
-------

* Stephan Mühlstrasser for developing circle-stdlib and for supporting this project.

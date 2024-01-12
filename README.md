# Rendervis

Rendervis is a minimalistic 3D renderer made using OpenGL and SDL2, written in C++. It is primarily designed to visualize results from physics-based animation algorithms and physics engines. It is cross-platform, self-contained and ready to go with minimal setup.

## Features

TODO

## Installation

Rendervis supports Windows and Linux (and technically any platforms supported by SDL, though this might not build out of the box). To build, Rendervis requires the following system dependencies:

- C++17 **Compiler** (tested on Clang/MSVC/GCC)
- **CMake** 3.19+
- Graphics Driver that supports **OpenGL 4.6**

Then follow these steps:

<u>1. Getting the source Code</u>

All library dependencies are already included in this repository as a submodule. Because of this, it is necessary to clone the repo with `--recurse-submodules` flag:

`git clone --recurse-submodules https://github.com/conrev/Rendervis`

<u>2. Building with CMake</u>

Once downloaded, we can simply follow the basic CMake build routine; from the root directory:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

or use any GUI/IDE that can build CMake projects (e.g. Visual Studio)

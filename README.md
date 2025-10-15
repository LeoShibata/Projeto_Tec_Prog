# Programming Techniques Project

A 2D game project developed for the Programming Techniques course using C++ and SFML.


## Requirements

### Prerequisites
**Before building, make sure you have installed:**

- [CMake](https://cmake.org/download/) (version 3.20 or higher)
- [MinGW-w64](https://www.mingw-w64.org/) or another CMake-compatible compiler
- [SFML 2.6.2](https://www.sfml-dev.org/download.php)

### SFML Setup
After building, make sure the following **.dll** files are in the same folder as the executable:

- `sfml-graphics-2.dll`
- `sfml-window-2.dll`
- `sfml-system-2.dll`


## Linux Compilation

Go to the build directory and digit:

```bash
cmake ..
make
```


## Compile on Windows

In the root of the project:

```bash
cmake -G "MinGW Makefiles" -S . -B build -DSFML_DIR="C:/SFML-2.6.2/lib/cmake/SFML"
cmake --build build
cd build
./SFMLgame
```

Or:

```bash
cmake -G "MinGW Makefiles" -S . -B build -DSFML_DIR="C:/SFML-2.6.2/lib/cmake/SFML"
cd build
mingw32-make
./SFMLgame
```

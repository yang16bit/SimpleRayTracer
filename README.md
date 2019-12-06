## At a Glance

A simple ray tracing based software renderer at children's play level, created for learning purpose.

![screen shot](README.md_resource/screenshot.jpg)

## Features

- Written in C++, applying C with class diagram.
- Crossing platforms by utilizing SDL2.
- Based on ray-object Intersecting test.
- Lighting & Shadow

## Build & Run

### Requirements

- Acknowledgement of compiling
- Linux or Windows. (Other desktop systems not tested.)
- GCC or MinGW or MSVC (Visual Studio 2017)
- CMake
- third party library: Catch2, SDL2.

### Build

#### For Linux and GCC

```shell
git clone REPO-URL
cd REPO-NAME
mkdir build-gcc
cd build-gcc
cmake -DCMAKE_BUILD_TYPE=Release -G "Makefiles" ..
make
./app
```

#### For MinGW

```shell
mkdir build-mingw
cd build-mingw
cmake .. -G "MinGW Makefiles"
mingw32-make -j 4
start app
```

#### For MSVC

```shell
mkdir build-msvc
cd build-msvc
cmake .. -G "Visual Studio 15 2017"
start app.sln
```

### USAGE

```shell
app [WIDTH HEIGHT]
```



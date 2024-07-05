# Amuse Editor 
Amuse is a multiplatform 2D/3D game engine written in C++. This is the editor for the engine.

## Screenshots

![Screenshot](https://raw.githubusercontent.com/darilrt/amuse-editor/master/docs/Screenshot%202024-07-02%20000633.png)

## Requirements

- CMake
- C++20 compiler
- Python 3

## Building

```bash
git clone --recursive https://github.com/darilrt/amuse-editor
cd amuse-editor
cmake -B build -S .
cmake --build build
```

## Running

```bash
cd build
./AmuseEditor
```
# Vally
![In development](https://img.shields.io/badge/-In%20development-orange) [![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://github.com/TheFrainD/Vally/blob/master/LICENSE)

Vally is basic 3D rendering engine made with C++ and OpenGL 4.6.

**The project is at its very early stage**

## Clone
```
git clone --recursive https://github.com/TheFrainD/Vally.git
```

## Build
```
cmake -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --config Release
```

## Dependencies
- [glfw](https://github.com/glfw/glfw) - window library
- [glad](https://glad.dav1d.de/) - OpenGL loading library
- [spdlog](https://github.com/gabime/spdlog.git) - logging library

## Implemented features
- Multiplatform windowing

## Planned features
- Global illumination
- Physically Based Shading
- Materials
- Multiplatform
- ECS
- Scene management
- Multithreading
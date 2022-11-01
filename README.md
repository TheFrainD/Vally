# Vally
![In development](https://img.shields.io/badge/-In%20development-orange) [![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://github.com/TheFrainD/Vally/blob/master/LICENSE)

![Vally](resources/logo300x300.png)

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
- [glad](https://glad.dav1d.de/) - OpenGL loader
- [spdlog](https://github.com/gabime/spdlog) - logging
- [imgui](https://github.com/ocornut/imgui) - GUI
- [glm](https://github.com/g-truc/glm) - Maths
- [stb-image](https://github.com/nothings/stb/blob/master/stb_image.h) - Image loading

## Implemented features
- Multiplatform windowing
- Event system (immediate event handling)

## Planned features
- Global illumination
- Physically Based Shading
- Materials
- Multiplatform
- ECS
- Scene management
- Multithreading
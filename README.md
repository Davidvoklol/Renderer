# Renderer

A renderer made in OpenGL

## Dependencies
- [cmake](https://cmake.org)
- C++ compiler

## Vendor

The repo uses

- [glfw](https://www.glfw.org/)
- [glad](https://glad.dav1d.de/)
- [glm](https://github.com/g-truc/glm.git)
- [stb_image.h](https://github.com/nothings/stb)

## Build and Run

### 0. Clone
```bash
git clone --recursive https://github.com/Davidvoklol/Renderer.git
cd Renderer
```

### 1. Config

> [!TIP]
> This generates config for the IDE to find header files

```bash
cmake -B build -S .
```

### 2. Build
```bash
cmake --build build
```

### 3. Run
`build/bin/Renderer`

# Renderer
A renderer made in c++ with OpenGL

## Dependencies
- [cmake](https://cmake.org)
- C++ compiler

## Vendor
- [glfw](https://www.glfw.org/)
- [glad](https://glad.dav1d.de/)
- [glm](https://github.com/g-truc/glm)
- [stb_image.h](https://github.com/nothings/stb)

## Config, Build and Run

### 0. Clone
```bash
git clone --recursive https://github.com/Davidvoklol/Renderer.git
```

### 1. Config
```bash
cmake -S . -B build
```

### 2. Build
```bash
cmake --build build 
```

### 3. Run
The executable will be `build/bin/Renderer`

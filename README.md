# Renderer

I'm making a renderer for a game in OpenGL

## Dependencies
- [cmake](https://cmake.org/)
- C++ compiler

## Vendor
- [glfw](https://www.glfw.org/download.html)
- [glad](https://glad.dav1d.de/) 
- [glm](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)

 ## Build

### 0. Clone
```bash
git clone --recursive https://github.com/Davidvoklol/Renderer.git
```

 ### 1. Config
 ```bash
 cmake -B build -S .
 ```

 ### 2. Build
 ```bash
 cmake --build build
 ```

 The executable will be in `build/bin`

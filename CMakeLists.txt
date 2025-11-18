cmake_minimum_required(VERSION 3.10)
project(Renderer)

set(OpenGL_GL_PREFERENCE "GLVND")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

# Disable unnecessary GLFW targets
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Don't build GLFW examples")
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "Don't build GLFW tests")
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "Don't build GLFW docs")
set(GLFW_INSTALL        OFF CACHE BOOL "Don't generate install targets")

file(GLOB SRC_FILES "src/*.cpp" "src/*/*.cpp")
file(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}/bin")

add_executable(Renderer
    ${SRC_FILES}
    "vendor/glad/src/glad.c"
    "vendor/stb/stb_image.c"
)

find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw EXCLUDE_FROM_ALL)

target_include_directories(Renderer PRIVATE 
    "vendor"
    "vendor/glfw/include"
    "vendor/glad/include"
)

target_link_libraries(Renderer PRIVATE 
    OpenGL::GL
    glfw
)

# Set the startup project
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY 
VS_STARTUP_PROJECT Renderer)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
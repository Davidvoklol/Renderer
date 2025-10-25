cmake_minimum_required(VERSION 3.10)
project(Renderer)

set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}/bin")
file(GLOB SRC_FILES "src/*.cpp")

add_executable(Renderer
	${SRC_FILES}
	vendor/glad/src/glad.c
	vendor/stb/stb_image.c
)

find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)

target_link_libraries(Renderer PRIVATE
	OpenGL::GL
	glfw
)

target_include_directories(Renderer PRIVATE
	vendor
	vendor/glfw/include
	vendor/glad/include
)

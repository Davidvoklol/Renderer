cmake_minimum_required(VERSION 3.10)
project(Renderer)

set(OpenGL_GL_PREFERENCE "GLVND")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_custom_target(copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/res"
	"${CMAKE_BINARY_DIR}/bin/res"
	COMMENT "Copying resources..."
)

file(GLOB SRC_FILES "src/*.cpp" "src/*/*.cpp")

add_executable(Renderer
	vendor/glad/src/glad.c
	${SRC_FILES}
)
add_dependencies(Renderer copy_resources)

find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)

target_link_libraries(Renderer PRIVATE
	OpenGL::GL
	glfw
)

target_include_directories(Renderer PRIVATE
	src
	vendor
	vendor/glfw/include
	vendor/glad/include
)

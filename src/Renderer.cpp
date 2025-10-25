#include "Renderer.hpp"
#include <iostream>

std::map<unsigned int, unsigned int> Renderer::buffer_cache;
unsigned int Renderer::shader_cache = 0;

void Renderer::BindBuffer(const unsigned int target, unsigned int id) {
	if (buffer_cache.find(target) == buffer_cache.end() || buffer_cache[target] != id) {
		buffer_cache[target] = id;
		switch (target) {
			case GL_ARRAY_BUFFER:
			case GL_ELEMENT_ARRAY_BUFFER: glBindBuffer(target, id); break;
			case GL_VERTEX_ARRAY: glBindVertexArray(id); break;
		}
	}
}

void Renderer::BindShader(const unsigned int id) {
	glUseProgram(id);
}

void Renderer::Update(GLFWwindow* window) {
        glfwSwapBuffers(window);
        glfwPollEvents();
};

void Renderer::Clear(const unsigned int mask) {
	glClear(mask);
}

unsigned int Renderer::GetBoundBuffer(const unsigned int target) {
	if (buffer_cache.find(target) != buffer_cache.end()) return buffer_cache[target];
	return 0;
}

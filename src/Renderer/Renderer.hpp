#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include <iostream>

class Renderer {
	private:
		static GLFWwindow* window;
		static unsigned int shader_cache;
		static unsigned int vertex_buffer_cache;
		static std::map<unsigned int, unsigned int> buffer_cache;
	public:
		static void Setup(unsigned int width, unsigned int height, const char* title, 
				GLFWmonitor* monitor, GLFWwindow* share);
		static void Terminate();

		static int WindowShouldClose();
		static void Clear(unsigned int mask);
		static void Update();

		static void BindBuffer(unsigned int target, unsigned int id);
		static void BindVertexBuffer(unsigned int id);
		static void BindShader(unsigned int id);
};

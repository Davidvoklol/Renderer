#pragma once

#include <map>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Renderer {
	private:
		static std::map<unsigned int, unsigned int> buffer_cache;
		static unsigned int shader_cache;
	public:
		static void BindBuffer(const unsigned int target, unsigned int id);
		static void BindShader(const unsigned int id);
		static void Update(GLFWwindow* window);
		static void Clear(const unsigned int mask);
		static unsigned int GetBoundBuffer(const unsigned int target);
};

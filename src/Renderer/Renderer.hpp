#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

class Renderer {
	private:
		static GLFWwindow* window;
	public:
		static void Setup(unsigned int width, unsigned int height, const char* title, 
				GLFWmonitor* monitor, GLFWwindow* share);
		static void Terminate();

};

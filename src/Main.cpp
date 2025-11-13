#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Common/Common.hpp"
#include "Renderer/Renderer.hpp"

int main() {
	Renderer::Setup(1280, 720, "", NULL, NULL);

	std::cout << glGetString(GL_VERSION) << "\n";

    while (!Renderer::WindowShouldClose()) {
		Renderer::Clear(GL_COLOR_BUFFER_BIT);

		Renderer::Update();
    }

	Renderer::Terminate();
    return 0;
}

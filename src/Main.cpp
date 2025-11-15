#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

#include "Common/Common.hpp"
#include "Renderer/Renderer.hpp"
#include "Vbo/Vbo.hpp"

struct Vertex {
	glm::vec2 position;
};

int main() {
	Renderer::Setup(1280, 720, "", NULL, NULL);

	std::cout << glGetString(GL_VERSION) << "\n";

	struct Vertex veritices[] = {
		{{ -0.5, -0.5 }},
		{{  0.5, -0.5 }},
		{{  0.5,  0.5 }},
		{{ -0.5,  0.5 }}
	};

	Vbo vbo(sizeof(veritices), veritices, GL_STATIC_DRAW, sizeof(struct Vertex));

    while (!Renderer::WindowShouldClose()) {
		Renderer::Clear(GL_COLOR_BUFFER_BIT);

		Renderer::Update();
    }

	Renderer::Terminate();
    return 0;
}

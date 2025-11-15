#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

#include "Common/Common.hpp"
#include "Renderer/Renderer.hpp"
#include "Vbo/Vbo.hpp"
#include "Ibo/Ibo.hpp"
#include "Shader/Shader.hpp"

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

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Vbo vbo(sizeof(veritices), veritices, GL_STATIC_DRAW, sizeof(struct Vertex));
	Ibo ibo(sizeof(indices), indices, GL_STATIC_DRAW, GL_FLOAT);

	std::filesystem::path program_path = Common::GetProgramPath();
	std::filesystem::path shader_path = program_path.append("res/shaders");
	
	Shader shader(shader_path.string() + "/vertex.glsl", shader_path.string() + "/fragment.glsl");

    while (!Renderer::WindowShouldClose()) {
		Renderer::Clear(GL_COLOR_BUFFER_BIT);

		Renderer::Update();
    }

	Renderer::Terminate();
    return 0;
}

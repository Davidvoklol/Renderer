#include "Vao.hpp"

Vao::Vao() {
	glGenVertexArrays(1, &id);
}

Vao::~Vao() {
	glDeleteVertexArrays(1, &id);
}

void Vao::Bind() const {
	Renderer::BindVertexBuffer(id);
}

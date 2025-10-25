#include "Ibo.hpp"
#include "Renderer.hpp"
#include <iostream>

Ibo::Ibo(const unsigned int size, const void* data, const unsigned int usage, const unsigned int type) {
	if (Renderer::GetBoundBuffer(GL_VERTEX_ARRAY) == 0)
		std::cerr << "(Ibo::Ibo) No vao is bound.\n";
	glGenBuffers(1, &id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	this->type = type;
	count = size / Common::GetGlTypeSize(type);
}

Ibo::~Ibo() {
	glDeleteBuffers(1, &id);
}

void Ibo::Bind() const {
	Renderer::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

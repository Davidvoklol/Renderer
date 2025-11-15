#include "Vbo.hpp"

Vbo::Vbo(unsigned int size, const void* data, unsigned int usage, unsigned int stride) {
	glGenBuffers(1, &id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	this->stride = stride;
}

Vbo::~Vbo() {
	glDeleteBuffers(1, &id);
}

void Vbo::Bind() const {
	Renderer::BindBuffer(GL_ARRAY_BUFFER, id);
}

unsigned int Vbo::GetStride() {
	return stride;
}

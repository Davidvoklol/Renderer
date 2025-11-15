#include "Ibo.hpp"

Ibo::Ibo(unsigned int size, const void* data, unsigned int usage, unsigned int type) {
	glGenBuffers(1, &id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	this->type = type;
	this->count = size / Common::GetGlTypeSize(type);
}

Ibo::~Ibo() {
	glDeleteBuffers(1, &id);
}

void Ibo::Bind() const {
	Renderer::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

unsigned int Ibo::GetType() const {
	return type;
}

unsigned int Ibo::GetCount() const {
	return count;
}

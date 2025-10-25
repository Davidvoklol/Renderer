#include "Vbo.hpp"

Vbo::Vbo(const unsigned int size, const void* data, const unsigned int usage) {
	glGenBuffers(1, &id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

Vbo::~Vbo() {
	glDeleteBuffers(1, &id);
}

void Vbo::Bind() const {
	Renderer::BindBuffer(GL_ARRAY_BUFFER, id);
};

void Vbo::AddLayoutElement(const unsigned int count, const unsigned int type) {
	layout_elements.push_back({ count, type, GL_FALSE });
	stride += Common::GetGlTypeSize(type);
}

#include "Vao.hpp"

Vao::Vao() {
	glGenVertexArrays(1, &id);
}

Vao::~Vao() {
	glDeleteVertexArrays(1, &id);
}

void Vao::Bind() const {
	Renderer::BindBuffer(GL_VERTEX_ARRAY, id);
}

void Vao::AddVboBinding(const Vbo& vbo) const {
	Bind();
	vbo.Bind();
	auto elements = vbo.layout_elements;
	unsigned int offset = 0;

	for (int i = 0, end = elements.size(); i < end; i++) {
		auto element = elements[i];
		glVertexAttribPointer(i,element.count, element.type, element.normalize, vbo.stride, (void*)(uintptr_t)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * Common::GetGlTypeSize(element.type);
	}
}

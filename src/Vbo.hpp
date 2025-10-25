#pragma once

#include <glad/glad.h>
#include <vector>
#include "Renderer.hpp"
#include "Common.hpp"

struct LayoutElement {
	unsigned int count;
	unsigned int type;
	unsigned int normalize;
};

class Vbo {
	private:
		unsigned int id;
	public:
		std::vector<LayoutElement> layout_elements;
		unsigned int stride = 0;

		Vbo(const unsigned int size, const void* data, const unsigned int usage);
		~Vbo();

		void Bind() const;

		void AddLayoutElement(const unsigned int count, const unsigned int type);
};

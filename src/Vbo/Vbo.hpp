#pragma once

#include <glad/glad.h>
#include "Renderer/Renderer.hpp"

class Vbo {
	private:
		unsigned int id;
		unsigned int stride;
	public:
		Vbo(unsigned int size, const void* data, unsigned int usage, unsigned int stride);
		~Vbo();

		void Bind() const;
		unsigned int GetStride();
};

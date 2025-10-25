#pragma once

#include <glad/glad.h>
#include "Vbo.hpp"
#include "Renderer.hpp"

class Vao {
	private:
		unsigned int id;
	public:
		Vao();
		~Vao();

		void Bind() const;

		void AddVboBinding(const Vbo& vbo) const;
};

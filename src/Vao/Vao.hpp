#pragma once

#include <glad/glad.h>
#include "Renderer/Renderer.hpp"

class Vao {
	private:
		unsigned int id;
	public:
		Vao();
		~Vao();

		void Bind() const;
};

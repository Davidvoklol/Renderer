#pragma once

#include <glad/glad.h>
#include "Renderer.hpp"
#include "Common.hpp"

class Ibo {
	private:
		unsigned int id;
	public:
		unsigned int count;
		unsigned int type;

		Ibo(const unsigned int size, const void* data, const unsigned int usage, const unsigned int type);
		~Ibo();

		void Bind() const;
};

#pragma once

#include <glad/glad.h>
#include "Renderer/Renderer.hpp"
#include "Common/Common.hpp"

class Ibo {
	private:
		unsigned int id;
		unsigned int type;
		unsigned int count;
	public:
		Ibo(unsigned int size, const void* data, unsigned int usage, unsigned int type);
		~Ibo();

		void Bind() const;
		unsigned int GetType() const;
		unsigned int GetCount() const;
};

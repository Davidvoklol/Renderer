#pragma once

#include <glad/glad.h>
#include "Renderer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

static unsigned int ParseShader(const char* path, const unsigned int type);

class Shader {
	private:
		unsigned int id;
	public:
		Shader(const std::string& vertex_path, const std::string& fragmet_path);
		~Shader();

		void Bind() const;
};

#pragma once

#include <glad/glad.h>
#include "Renderer/Renderer.hpp"
#include <fstream>
#include <string>

class Shader {
	private:
		std::string vertex_path;
		std::string fragment_path;
		unsigned int id;
	public:
		Shader(const std::string& vertex_path, const std::string& fragment_path);
		~Shader();

		void Load();
		void Bind() const;
};

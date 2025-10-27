#pragma once

#include <glad/glad.h>
#include "Renderer.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <map>
#include <sstream>
#include <iostream>

static unsigned int ParseShader(const char* path, const unsigned int type);

class Shader {
	private:
		unsigned int id;
		mutable std::map<const char*, unsigned int> uniform_cache;
		unsigned int GetUniformLocation(const char* name) const;
	public:
		Shader(const std::string& vertex_path, const std::string& fragmet_path);
		~Shader();

		void Bind() const;

		void SetUniformMat4(const char* name, const glm::mat4& value) const;
};

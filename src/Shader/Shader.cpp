#include "Shader.hpp"
#include <string>

static unsigned int CompileShader(const std::string& path, unsigned int type) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
		std::cerr << "[Shader.cpp - CompileShader] Failed to open file: " << path << "\b";
		return 0;
	}

	std::vector<char> buffer(file.tellg());    
	file.seekg(0);
	if (!file.read(buffer.data(), buffer.size())) {
		std::cerr << "[Shader.cpp - CompileShader] Failed to read file: " << path << "\n";
		return 0;
    }
	buffer.push_back('\0');

	char* src = &buffer[0];
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> message(length);
		glGetShaderInfoLog(id, length, nullptr, message.data());
		std::cerr << "[Shader.cpp - CompileShader] Failed to compile " 
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader\n\t" << message.data() << "\n";
		glDeleteShader(id);
		return 0;
	}

	return id;
}


Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
	this->vertex_path = vertex_path;
	this->fragment_path = fragment_path;
	id = glCreateProgram();
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::Load() {
	unsigned int vs = CompileShader(vertex_path, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragment_path, GL_FRAGMENT_SHADER);

	if (vs == 0 || fs == 0) {
		std::cerr << "[Shader::Load] Failed to load shader\n";
		return;
	}

	glAttachShader(id, vs);
	glAttachShader(id, fs);

	glLinkProgram(id);

	int succsss;
	glGetProgramiv(id, GL_LINK_STATUS, &succsss);
	if (!succsss) {
		int length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length);
		glGetProgramInfoLog(id, length, NULL, message);

		std::cerr << "[Shader.cpp - Load] Failed to link shader: \n\t" << message << "\n";
	}

	glDetachShader(id, vs);
	glDetachShader(id, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
};

void Shader::Bind() const {
	Renderer::BindShader(id);
}

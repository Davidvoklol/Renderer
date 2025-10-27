#include "Shader.hpp"

static unsigned int ParseShader(const std::string& path, const unsigned int type) {
	std::string code;
    std::ifstream file;
	file.open(path);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << path << "\n";
		return 0;
	}

	std::stringstream shader_stream;
	shader_stream << file.rdbuf();

	file.close();
	code = shader_stream.str();
	const char* src = code.c_str();

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* buffer = (char*)malloc(length);
		glGetShaderInfoLog(shader, length, nullptr, buffer);
		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
			" shader:\n" << buffer;
		free(buffer);
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
	unsigned int vs = ParseShader(vertex_path, GL_VERTEX_SHADER);
	unsigned int fs = ParseShader(fragment_path, GL_FRAGMENT_SHADER);

	if (vs <= 0 || fs <= 0) {
		std::cerr << "Failed to initialize shader.\n";
		return;
	}

	id = glCreateProgram();

	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);

	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* buffer = (char*)malloc(length);
		glGetProgramInfoLog(id, length, nullptr, buffer);
		std::cerr << "Failed to link program:\n" << buffer;
		free(buffer);
		glDeleteProgram(id);
		id = 0;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::Bind() const {
	Renderer::BindShader(id);
}

unsigned int Shader::GetUniformLocation(const char* name) const {
	if (uniform_cache.find(name) == uniform_cache.end()) 
		uniform_cache[name] = glGetUniformLocation(id, name);
	return uniform_cache[name];
}

void Shader::SetUniformMat4(const char* name, const glm::mat4& value) const {
	Bind();
	unsigned int loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

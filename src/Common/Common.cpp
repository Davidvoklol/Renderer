#include "Common.hpp"
#include <filesystem>
#include <iostream>

unsigned int Common::GetGlTypeSize(const GLenum type) {
	switch (type) {
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_INT: return sizeof(GLint);
		case GL_FLOAT: return sizeof(GLfloat);
	}

	std::cerr << "[Common::GetGlTypeSize] Unknown type: " << type << "\n";
	return 0;
}

std::filesystem::path Common::GetProgramPath() {
    char buffer[
    #if defined(_WIN32)
        MAX_PATH
    #else
        PATH_MAX
    #endif
    ] = {0};

#if defined(_WIN32)
    DWORD len = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    if (len == 0 || len == MAX_PATH) {
		std::cerr << "[Common::GetProgramPath] Failed to get program path\n";
		return "";
	}

#elif defined(__APPLE__)
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) != 0) {
		std::cerr << "[Common::GetProgramPath] Failed to get program path\n";
		return ""
	}

#elif defined(__linux__)
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
	if (len == -1) {
		std::cerr << "[Common::GetProgramPath] Failed to get program path\n";
		return "";
	}
    buffer[len] = '\0';
#endif

    return std::filesystem::path(buffer).parent_path();
}

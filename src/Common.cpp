#include "Common.hpp"

std::string Common::GetProgramPath() {
	std::string exePath;

#if defined(__linux__)
	char path[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
	if (count != -1) {
		path[count] = '\0';
		exePath = path;
	}

#elif defined(_WIN32) || defined(_WIN64)
	char path[MAX_PATH];
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
		DWORD result = GetModuleFileName(hModule, path, MAX_PATH);
		if (result != 0) exePath = path;
	}

#elif defined(__APPLE__) || defined(__MACH__) 
	uint32_t size = 0;
	_NSGetExecutablePath(nullptr, &size);
	std::vector<char> buffer(size);
	if (_NSGetExecutablePath(buffer.data(), &size) == 0) exePath = buffer.data();

#else
	std::cerr << "Failed to detect operating system." << std::endl;
	std::exit(1);
#endif

	if (exePath.empty()) {
		std::cerr << "Failed to get program path." << std::endl;
		std::exit(1);
	}

	return std::filesystem::path(exePath).parent_path().string();
}

unsigned int Common::GetGlTypeSize(const unsigned int type) {
	switch (type) {
		case GL_INT: return sizeof(GLint);
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
	}
	std::cerr << "(Common::GetGlTypeSize) Unknown type [" << type << "]\n";
	return 0;
}

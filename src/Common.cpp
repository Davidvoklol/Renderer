#include "Common.hpp"

std::string Common::GetProgramPath() {

#if defined(__linux__)
	char path[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
	if (count != -1) {
		path[count] = '\0';
		return path;
	}

#elif defined(_WIN32) || defined(_WIN64)
	char path[MAX_PATH];
    HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
        DWORD result = GetModuleFileName(hModule, path, MAX_PATH);
        if (result != 0) return path;
    }

#elif defined(__APPLE__) || defined(__MACH__) 
	uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::vector<char> buffer(size);
	if (_NSGetExecutablePath(buffer.data(), &size) == 0) return std::string(buffer.data());

#else
		std::cerr << "Couldn't detect operating system."
		std::exit(1);
#endif

	std::cerr << "Failed to get program path." << std::endl;
	std::exit(1);
}

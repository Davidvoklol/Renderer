#pragma once

#include <glad/glad.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <limits.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif

class Common {
	public:
		static unsigned int GetGlTypeSize(const GLenum type);
		static std::filesystem::path GetProgramPath();
};

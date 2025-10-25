#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <filesystem>

#if defined(__linux__)
#include <unistd.h>
#include <limits.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <string>
#elif defined(__APPLE__) || defined(__MACH__) 
#include <mach-o/dyld.h>
#include <vector>
#endif

class Common {
	public:
		static std::string GetProgramPath();
		static unsigned int GetGlTypeSize(const unsigned int type);
};

#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <algorithm>

class Event {
	using KeyCallbackType = void(*)(GLFWwindow*, int, int, int, int);

	private:
		static std::vector<KeyCallbackType> key_callbacks;
	public:
		static void TriggerCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void AddKeyCallback(const KeyCallbackType callback);
		static void RemoveCallback(const KeyCallbackType callback);
};

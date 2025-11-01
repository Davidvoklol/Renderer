#include "Event.hpp"
#include "GLFW/glfw3.h"

using KeyCallbackType = void (*)(GLFWwindow*, int, int, int, int);

std::vector<KeyCallbackType> Event::key_callbacks;

void Event::TriggerCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for (KeyCallbackType func : key_callbacks) {
		func(window, key, scancode, action, mods);
	}
}

void Event::AddKeyCallback(const KeyCallbackType callback) {
	if (std::find(key_callbacks.begin(), key_callbacks.end(), callback) == key_callbacks.end()) {
		key_callbacks.push_back(callback);
	}
}

void Event::RemoveCallback(const KeyCallbackType callback) {
	auto it = std::find(key_callbacks.begin(), key_callbacks.end(), callback);
	if(it != key_callbacks.end()) key_callbacks.erase(it);
}

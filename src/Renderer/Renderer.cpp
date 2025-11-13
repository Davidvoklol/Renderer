#include "Renderer.hpp"

GLFWwindow* Renderer::window = 0;
unsigned int Renderer::shader_cache = 0;
unsigned int Renderer::vertex_buffer_cache = 0;
std::map<unsigned int, unsigned int> Renderer::buffer_cache;

void Renderer::Setup(unsigned int width, unsigned int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
    if (!glfwInit()) {
		std::cerr << "[Renderer::Setup] Failed to initialize glfw\n";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, monitor, share);
    if (!window) {
        glfwTerminate();
		std::cerr << "[Renderer::Setup] Failed to create window\n";
		return;
    }

    glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "[Renderer::Setup] Failed to initialize OpenGL context\n";
		return;
	}
}

void Renderer::Terminate() {
	glfwTerminate();
}

int Renderer::WindowShouldClose() {
	return glfwWindowShouldClose(window);
}

void Renderer::Clear(unsigned int mask) {
	glClear(mask);
}

void Renderer::Update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::BindBuffer(unsigned int target, unsigned int id) {
	if (buffer_cache.find(target) == buffer_cache.end() || buffer_cache[target] != id) {
		glBindBuffer(target, id);
		buffer_cache[target] = id;
	}
}

void Renderer::BindVertexBuffer(unsigned int id) {
	if (vertex_buffer_cache != id) {
		glBindVertexArray(id);
		vertex_buffer_cache = id;
	}
}

void Renderer::BindShader(unsigned int id) {
	if (shader_cache != id) {
		glUseProgram(id);
		shader_cache = id;
	}
}

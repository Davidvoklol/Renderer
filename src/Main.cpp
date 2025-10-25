#include "Common.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Renderer.hpp"
#include "Vbo.hpp"
#include "Vao.hpp"
#include "Ibo.hpp"
#include "Shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(1280, 720, "Renderer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context\n";
        return -1;
    }
	std::cout << glGetString(GL_VERSION) << "\n";


	float vertices[] = {
	    -0.5, -0.5, 1.0, 0.0, 0.0,
	    -0.5,  0.5, 0.0, 1.0, 0.0,
	     0.5,  0.5, 0.0, 0.0, 1.0,
	     0.5, -0.5, 1.0, 1.0, 1.0
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Vao vao;
	vao.Bind();

	Vbo vbo(sizeof(vertices), vertices, GL_STATIC_DRAW);
	vbo.AddLayoutElement(2, GL_FLOAT);
	vbo.AddLayoutElement(3, GL_FLOAT);

	Ibo ib(sizeof(indices), indices, GL_STATIC_DRAW, GL_UNSIGNED_INT);

	vao.AddVboBinding(vbo);

	std::string path = Common::GetProgramPath();

	Shader shader(path + "/res/shaders/vertex.glsl", path + "/res/shaders/fragment.glsl");
	shader.Bind();

	glClearColor(0.1, 0.1, 0.1, 1.0);
    while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

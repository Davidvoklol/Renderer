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
#include "Camera.hpp"
#include "Event.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera camera;
float CamSpeed = 1.0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {
	float WIDTH = 1280, HEIGHT = 720;

    GLFWwindow* window;

    if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, Event::TriggerCallbacks);
	
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context\n";
        return -1;
    }
	std::cout << glGetString(GL_VERSION) << "\n";


	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	struct Vertex vertices[] = {
		{ { -0.5, -0.5, 1.0 }, { 1.0, 0.0, 0.0 } },
		{ { -0.5,  0.5, 1.0 }, { 0.0, 1.0, 0.0 } },
	    { {  0.5,  0.5, 1.0 }, { 0.0, 0.0, 1.0 } },
	    { {  0.5, -0.5, 1.0 }, { 1.0, 1.0, 1.0 } }
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Vao vao;
	vao.Bind();

	Vbo vbo(sizeof(vertices), vertices, GL_STATIC_DRAW);
	vbo.AddLayoutElement(3, GL_FLOAT);
	vbo.AddLayoutElement(3, GL_FLOAT);

	Ibo ibo(sizeof(indices), indices, GL_STATIC_DRAW, GL_UNSIGNED_INT);

	vao.AddVboBinding(vbo);

	camera.MoveTo(glm::vec3(0, 0, -5));
	camera.LookAt(glm::vec3(0));
	camera.SetPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100.0);

	std::string path = Common::GetProgramPath();
	Shader shader(path + "/res/shaders/vertex.glsl", path + "/res/shaders/fragment.glsl");
	shader.SetUniformMat4("proj", camera.GetProjectionMatrix());
	shader.SetUniformMat4("model", glm::mat4(1.0f));
	shader.Bind();

	glm::mat4 view_cache;

	glClearColor(0.1, 0.1, 0.1, 1.0);
	while (!glfwWindowShouldClose(window)) {
		Renderer::Clear(GL_COLOR_BUFFER_BIT);

		glm::mat4 view = camera.GetViewMatrix();
		if (view != view_cache) {
			shader.SetUniformMat4("view", view);
			view_cache = view;
		}

		glDrawElements(GL_TRIANGLES, ibo.count, ibo.type, nullptr);

		Renderer::Update(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		glm::vec3 cam_dir = camera.GetDirection();
		glm::vec3 cam_right = camera.GetRightVec();
		switch (key) {
			case GLFW_KEY_W:
				camera.Move(cam_dir * CamSpeed);
				break;
			case GLFW_KEY_S:
				camera.Move(cam_dir * -CamSpeed);
				break;
			case GLFW_KEY_A:
				camera.Move(cam_right * -CamSpeed);
				break;
			case GLFW_KEY_D:
				camera.Move(cam_right * CamSpeed);
				break;
		}
	}
}

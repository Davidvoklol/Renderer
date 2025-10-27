#include <cstddef>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Common.hpp"
#include "Renderer.hpp"
#include "Vbo.hpp"
#include "Vao.hpp"
#include "Ibo.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Event.hpp"
#include "glm/fwd.hpp"

struct Cursor {
	glm::vec2 position = glm::vec2(-1, -1);
	glm::vec2 offset = glm::vec2(0, 0);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

Cursor cursor;
Camera camera;
float CamSpeed = 2.5;
float CamSensitivity = 0.1f;
glm::vec3 CamMovement = glm::vec3(0);

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
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	
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
	camera.LookAt(glm::vec3(0, 0, 0));
	camera.SetPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100.0);

	std::string path = Common::GetProgramPath();
	Shader shader(path + "/res/shaders/vertex.glsl", path + "/res/shaders/fragment.glsl");
	shader.SetUniformMat4("proj", camera.GetProjectionMatrix());
	shader.SetUniformMat4("model", glm::mat4(1.0f));
	shader.Bind();

	glm::mat4 view_cache;

	float last_time = glfwGetTime();
	float delta_time = 0;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	while (!glfwWindowShouldClose(window)) {
		Renderer::Clear(GL_COLOR_BUFFER_BIT);

		float now = glfwGetTime();
		delta_time = now - last_time;
		last_time = now;

		camera.Move(CamMovement * CamSpeed * delta_time);
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
	glm::vec3 cam_dir = camera.GetDirection();
	glm::vec3 cam_right = camera.GetRightVec();
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		float x = CamMovement.x,
			  y = CamMovement.y,
			  z = CamMovement.z;
		switch (key) {
			case GLFW_KEY_W: if (z !=  1) CamMovement.z +=  1; break;
			case GLFW_KEY_S: if (z != -1) CamMovement.z += -1; break;
			case GLFW_KEY_A: if (x != -1) CamMovement.x += -1; break;
			case GLFW_KEY_D: if (x !=  1) CamMovement.x +=  1; break;
			case GLFW_KEY_SPACE: if (y != 1) CamMovement.y += 1; break;
			case GLFW_KEY_LEFT_CONTROL: if (y != -1) CamMovement.y += -1; break;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W:
			case GLFW_KEY_S: CamMovement.z = 0; break;
			case GLFW_KEY_A:
			case GLFW_KEY_D: CamMovement.x = 0; break;
			case GLFW_KEY_SPACE:
			case GLFW_KEY_LEFT_CONTROL: CamMovement.y = 0; break;
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	glm::vec2 new_pos = glm::vec2(xpos, ypos);
	if (cursor.position.x != -1) {
		cursor.offset = new_pos - cursor.position;

		// (0, 0) is top left

		float yaw = cursor.offset.x * CamSensitivity;		
		float pitch = -cursor.offset.y * CamSensitivity;

		camera.Turn(pitch, yaw);
	}
	cursor.position = new_pos;
}

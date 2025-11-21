#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void) {
	GLFWwindow *window;

	if (!glfwInit()) {
		std::cerr << "Failed to initialize glfw";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize";
		return -1;
	}
	std::cout << glGetString(GL_VERSION) << "\n";

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertices[] = {
		-0.5, -0.5, 1.0, 0.0, 0.0,
		 0.5, -0.5, 0.0, 1.0, 0.0,
		 0.5,  0.5, 0.0, 0.0, 1.0,
		-0.5,  0.5, 1.0, 1.0, 1.0
	};
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)(2 * sizeof(float)));
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	unsigned int shader = glCreateProgram();

	const char *vertex_src =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec2 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"out vec4 Color;\n"
		"\n"
		"void main() {\n"
		"	 gl_Position = vec4(position, 1.0, 1.0);\n"
		"  Color = vec4(color, 1.0);\n"
		"}\n";
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_src, NULL);
	glCompileShader(vs);

	const char *fragment_src =
		"#version 330 core\n"
		"\n"
		"in vec4 Color;"
		"out vec4 FragColor;"
		"\n"
		"void main() {\n"
		"	 FragColor = Color;"
		"}\n";
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_src, NULL);
	glCompileShader(fs);

	glAttachShader(shader, vs);
	glAttachShader(shader, fs);

	glLinkProgram(shader);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

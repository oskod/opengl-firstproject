#ifdef DEBUG
#include <stdio.h>
#else
// all printf gone if debug is undefined
#define printf(...) (void)0
#endif

#include <math.h>

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

const int width = 800;
const int height = 600;

void __framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec2 pos;\n"
	"void main() {\n"
	"	gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);\n"
	"}";
const char* fragmentShaderSource = 
	"#version 330 core\n"
	"out vec4 fragColor;\n"
	"uniform vec4 ourColor;"
	"void main() {\n"
	"	fragColor = ourColor;\n"
	"}";

int main() {
	printf("Hello, OpenGL!\n");

	// glfw initialize and config
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(width, height, "Hello, OpenGL!", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create window\n");

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, __framebufferSizeCallback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");

		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, width, height);

	// shader compilation and linking
	int success;
	char infoLog[512];

	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("OPENGL VERTEX SHADER COMPILATION FAILED\n%s", infoLog);

		glfwTerminate();
		return -1;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("OPENGL FRAGMENT SHADER COMPILATION FAILED\n%s", infoLog);

		glfwTerminate();
		return -1;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("OPENGL PROGRAM LINKING FAILED\n%s", infoLog);

		glfwTerminate();
		return -1;
	}

	// no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ahh triangle
	float vertices[] = {
		0.0f, 0.5f, 0.0f, // top
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f // bottom right
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind vertex array, every buffer bound while this one is bound, will usually be linked to this
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// tell opengl how to use the data from the buffer, this gets registered in the vertex array
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// vertexattribpointer registers VBO as the VAO's vertex buffer, so we can safely unbind this now
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate shader
		glUseProgram(shaderProgram);

		// ourColor uniform
		float elapsed = glfwGetTime();
		float sine = sin(elapsed) * 0.5f + 0.5f;
		int colorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(colorLocation, 1.0f - sine, 1.0f - sine, sine, 1.0f);

		// render triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0) // unbinding this is unnessecary as we use it every frame anyway

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void __framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}
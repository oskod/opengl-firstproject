#ifdef DEBUG
#include <stdio.h>
#else
// all printf gone if debug is undefined
#define printf(...) (void)0
#endif

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

const int width = 800;
const int height = 600;

void __framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main() {\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
	"}";
const char* fragmentShaderSource = 
	"#version 330 core\n"
	"out vec4 fragColor;\n"
	"void main() {\n"
	"	fragColor = vec4(0.5f, 0.2f, 1.0f, 1.0f);\n"
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
	GLFWwindow* window = glfwCreateWindow(width, height, "my first opengl project!!!!!!", NULL, NULL);
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

	// shaders
	int success;
	char infoLog[512];

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	// compile vertex shader
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

	// compile fragment shader
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

	// create shader program and attach shaders
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("OPENGL SHADER PROGRAM LINKING FAILED\n%s", infoLog);
		
		glfwTerminate();
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// create first triangle
	
	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};
	unsigned int faces[] = {
		0, 1, 3,
		1, 2, 3
	};


	// buffers
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind vertex array, so all buffers get stored in it
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // to opengl: hey, this is the buffer you need to write to when writing data to GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// doesn't sizeof(vertices) give the size of the pointer and not the array? I'll have to do some research later.

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

	// tell opengl how to read the data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// unbind vertex array before the buffers, to ensure the bound buffers are stored in it
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.11f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// render instructions are finished, swap buffers and render to the screen
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// kill everything
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void __framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	printf("Resize %d %d\n", width, height);
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		printf("goodbye guys\n");
		glfwSetWindowShouldClose(window, 1);
	}
}
#ifdef DEBUG
#include <stdio.h>
#else
// all printf gone if debug is undefined
#define printf(...) (void)0
#endif

#include "shader.h"

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"


const int width = 800;
const int height = 600;

const char* vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 pos;\n"
	"layout (location = 1) in vec3 color;\n"
	"out vec3 vertColor;\n"
	"void main() {\n"
	"	gl_Position = vec4(pos, 1.0f);\n"
	"	vertColor = color;\n"
	"}";
const char* fragmentShaderSource = 
	"#version 330 core\n"
	"in vec3 vertColor;\n"
	"out vec4 fragColor;\n"
	"void main() {\n"
	"	fragColor = vec4(vertColor, 1.0f);\n"
	"}";

void __framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
	unsigned int vertexShader;
	if (!compileShader(&vertexShader, GL_VERTEX_SHADER, vertexShaderSource)) {
		glDeleteShader(vertexShader);
		glfwTerminate();

		return -1;
	}

	unsigned int fragmentShader;
	if (!compileShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource)) {
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glfwTerminate();

		return -1;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if (!linkProgram(shaderProgram)) {
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
		glfwTerminate();

		return -1;
	}

	// no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ahh triangle
	float vertices[] = {
		// pos               // color
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f // bottom right
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind vertex array, every buffer bound while this one is bound, will usually be linked to this
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// tell opengl how to use the data from the buffer, this gets registered in the vertex array
		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// vertexattribpointer registers VBO as the VAO's vertex buffer, so we can safely unbind this now
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
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
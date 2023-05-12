#ifdef DEBUG
#include <stdio.h>
#else
#define printf(...) (void)0
#endif

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

const int width = 800;
const int height = 600;

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

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render instructions are finished, swap buffers and render to the screen
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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
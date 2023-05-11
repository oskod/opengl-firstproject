#ifdef DEBUG
#include <stdio.h>
#endif

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

void __framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
#ifdef DEBUG
	printf("Hello, OpenGL!\n");
#endif

	// glfw initialize and config
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "my first opengl project!!!!!!", NULL, NULL);
	if (window == NULL) {
		#ifdef DEBUG
		printf("Failed to create window\n");
		#endif

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, __framebufferSizeCallback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		#ifdef DEBUG
		printf("Failed to initialize GLAD\n");
		#endif

		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);

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
	#ifdef DEBUG
	printf("Resize %d %d\n", width, height);
	#endif
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		printf("goodbye guys\n");
		glfwSetWindowShouldClose(window, 1);
	}
}
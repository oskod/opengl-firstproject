#ifdef DEBUG
#include <stdio.h>
#endif

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

void __framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	#ifdef DEBUG
	printf("Hello, OpenGL!");
	#endif

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "my first opengl!!!!!!", NULL, NULL);
	if (window == NULL) {
		#ifdef DEBUG
		printf("Failed to create window");
		#endif

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		#ifdef DEBUG
		printf("Failed to initialize GLAD");
		#endif

		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, __framebufferSizeCallback);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
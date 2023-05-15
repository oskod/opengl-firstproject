#ifdef DEBUG
#include <stdio.h>
#else
// all printf gone if debug is undefined
#define printf(...) (void)0
#endif

#include <GLAD/glad.h>

int compileShader(unsigned int* shaderId, unsigned int shaderType, const char* shaderSource) {
	*shaderId = glCreateShader(shaderType);

	glShaderSource(*shaderId, 1, &shaderSource, NULL);
	glCompileShader(*shaderId);

	int success;
	char infoLog[512];
	glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shaderId, 512, NULL, infoLog);
		printf("Shader compilation error:\n%s", infoLog);

		return 0;
	}

	return 1;
}

int linkProgram(unsigned int programId) {
	glLinkProgram(programId);

	int success;
	char infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(programId, 512, NULL, infoLog);
		printf("OPENGL PROGRAM LINKING FAILED\n%s", infoLog);

		return 0;
	}

	return 1;
}
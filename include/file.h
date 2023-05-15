#include <stdio.h>
#include <stdlib.h>

const char* readFile(const char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		return '\0';
	}

	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	char* buff = (char*)malloc(size);
	fgets(buff, size, fp);

	fclose(fp);
	return buff;
}
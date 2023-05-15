#include <stdio.h>
#include <stdlib.h>

const char* readFile(const char* fileName) {
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) {
		return '\0';
	}
	
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	char* buf = (char*)malloc(size * sizeof(char) + 1);
	fread(buf, sizeof(char), size, fp);
	buf[size] = '\0';

	fclose(fp);
	return buf;
}
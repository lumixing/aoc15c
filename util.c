#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void panic(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	fprintf(stderr, "PANIC: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");

	va_end(args);
	exit(1);
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

typedef struct {
	FILE *file;
	char *buf;
	size_t len;
} File;

File read_file(char *path) {
	FILE *file = fopen(path, "rb");
	if (!file) {
		panic("could not open file: %s", path);
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buf = malloc(file_size);
	if (!buf) {
		panic("could not alloc file (%ld bytes)", file_size);
	}

	fread(buf, 1, file_size, file);

	return (File){file, buf, file_size};
}

void file_free(File file) {
	fclose(file.file);
	free(file.buf);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util.c"

int part_one(File file);
int part_two(File file);

int main() {
	File file = read_file("input.txt");

	int ans_one = part_one(file);
	printf("answer one: %d\n", ans_one);

	int ans_two = part_two(file);
	printf("answer two: %d\n", ans_two);

	file_free(file);

	return 0;
}

int part_one(File file) {
	int sum = 0;

	// strtok modifies the string, so create a copy
	char* file_buf_copy = strdup(file.buf);

	char* line = strtok(file_buf_copy, "\n");
	while (line) {
		int x, y, z;
		sscanf(line, "%dx%dx%d", &x, &y, &z);

		int xy = x * y;
		int yz = y * z;
		int zx = z * x;

		int mx = min(min(xy, yz), min(yz, zx));

		sum += xy * 2 + yz * 2 + zx * 2 + mx;

		line = strtok(NULL, "\n");
	}

	free(file_buf_copy);

	return sum;
}

int part_two(File file) {
	int sum = 0;

	char* line = strtok(file.buf, "\n");
	while (line) {
		int x, y, z;
		sscanf(line, "%dx%dx%d", &x, &y, &z);

		int mx = max(max(x, y), max(y, z));

		if (mx == x) {
			sum += y * 2 + z * 2;
		} else if (mx == y) {
			sum += x * 2 + z * 2;
		} else {
			sum += x * 2 + y * 2;
		}

		sum += x * y * z;

		line = strtok(NULL, "\n");
	}

	return sum;
}

#include <stdio.h>
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
	return 0;
}

int part_two(File file) {
	return 0;
}

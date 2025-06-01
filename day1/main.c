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
	int counter = 0;

	for (int i = 0; i < file.len; i++) {
		char ch = file.buf[i];

		switch (ch) {
		case '(':
			counter += 1;
			break;
		case ')':
			counter -= 1;
			break;
		default:
			panic("invalid character: %d", ch);
			break;
		}
	}

	return counter;
}

int part_two(File file) {
	int counter = 0;

	for (int i = 0; i < file.len; i++) {
		char ch = file.buf[i];

		switch (ch) {
		case '(':
			counter += 1;
			break;
		case ')':
			counter -= 1;
			break;
		default:
			panic("invalid character: %d", ch);
			break;
		}

		if (counter == -1)
			return i + 1;
	}

	panic("could not find position");
	return -1;
}

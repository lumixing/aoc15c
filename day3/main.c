#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../util.c"

typedef struct {
	int x, y;
} Point;

bool point_eq(Point p1, Point p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

typedef struct {
	size_t len, cap;
	Point *buf;
} DynArrPoint;

DynArrPoint dyn_arr_point_init(size_t init_cap) {
	DynArrPoint dyn_arr;
	dyn_arr.len = 0;
	dyn_arr.cap = init_cap;
	dyn_arr.buf = malloc(init_cap * sizeof(Point));

	if (!dyn_arr.buf) {
		panic("could not malloc dyn arr buf (%d bytes)", init_cap * sizeof(Point));
	}

	return dyn_arr;
}

void dyn_arr_point_free(DynArrPoint dyn_arr) {
	free(dyn_arr.buf);
}

void dyn_arr_point_append(DynArrPoint *dyn_arr, Point point) {
	if (dyn_arr->len + 1 >= dyn_arr->cap) {
		dyn_arr->cap *= 2;
		dyn_arr->buf = realloc(dyn_arr->buf, dyn_arr->cap * sizeof(Point));

		if (!dyn_arr->buf) {
			panic("could not realloc dyn arr buf (%d bytes)", dyn_arr->cap * sizeof(Point));
		}
	}

	dyn_arr->buf[dyn_arr->len++] = point;
}

bool dyn_arr_point_contains(DynArrPoint dyn_arr, Point point) {
	for (int i = 0; i < dyn_arr.len; i++) {
		if (point_eq(point, dyn_arr.buf[i]))
			return true;
	}

	return false;
}

void dyn_arr_point_print(DynArrPoint dyn_arr) {
	printf("printing %zu points\n", dyn_arr.len);
	for (int i = 0; i < dyn_arr.len; i++) {
		Point p = dyn_arr.buf[i];
		printf("%d -> (%d, %d)\n", i, p.x, p.y);
	}
}

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
	Point position = (Point){0, 0};

	DynArrPoint dyn_arr = dyn_arr_point_init(256);
	dyn_arr_point_append(&dyn_arr, position);

	for (int i = 0; i < file.len; i++) {
		char ch = file.buf[i];

		switch (ch) {
		case '>':
			position.x += 1;
			break;
		case '<':
			position.x -= 1;
			break;
		case '^':
			position.y += 1;
			break;
		case 'v':
			position.y -= 1;
			break;
		default:
			panic("invalid char %d", ch);
		}

		if (!dyn_arr_point_contains(dyn_arr, position)) {
			dyn_arr_point_append(&dyn_arr, position);
		}
	}

	dyn_arr_point_free(dyn_arr);

	return dyn_arr.len;
}

int part_two(File file) {
	Point pos_santa = (Point){0, 0};
	Point pos_robo = (Point){0, 0};

	DynArrPoint dyn_arr_santa = dyn_arr_point_init(256);
	dyn_arr_point_append(&dyn_arr_santa, pos_santa);

	DynArrPoint dyn_arr_robo = dyn_arr_point_init(256);

	for (int i = 0; i < file.len; i++) {
		char ch = file.buf[i];
		bool santa_turn = i % 2 == 0;
		Point *position = santa_turn ? &pos_santa : &pos_robo;
		DynArrPoint *dyn_arr = santa_turn ? &dyn_arr_santa : &dyn_arr_robo;

		switch (ch) {
		case '>':
			position->x += 1;
			break;
		case '<':
			position->x -= 1;
			break;
		case '^':
			position->y += 1;
			break;
		case 'v':
			position->y -= 1;
			break;
		default:
			panic("invalid char %d", ch);
		}

		if (!dyn_arr_point_contains(dyn_arr_santa, *position) && !dyn_arr_point_contains(dyn_arr_robo, *position)) {
			dyn_arr_point_append(dyn_arr, *position);
		}
	}

	dyn_arr_point_free(dyn_arr_santa);
	dyn_arr_point_free(dyn_arr_robo);

	return dyn_arr_santa.len + dyn_arr_robo.len;
}

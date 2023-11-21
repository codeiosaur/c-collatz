#include <stdio.h>
#include <limits.h>

struct uintCollatzStepInfo{
	unsigned int step_count, max;
};

typedef struct uintCollatzStepInfo Struct_uint;

unsigned int collatz(unsigned int collatz) {
	unsigned int step_count = 0;
	unsigned int max = 0;
	while (collatz != 1) {
		if (collatz >= max) {
			max = collatz;
		}
		if (collatz % 2 == 0) {
			collatz /= 2;
			printf("%d\n", collatz);
		}
		else {
			collatz = (3 * collatz) + 1;
			printf("%d\n", collatz);
		}
		step_count++;
	}
	printf("Highest Step Ever: %u\n", max);
	return step_count;
}

Struct_uint uint_collatz_struct(unsigned int collatz) {
	Struct_uint info;
	info.max = 0;
	info.step_count = 0;
	while (collatz != 1) {
		if (collatz >= info.max) {
			info.max = collatz;
		}
		if (collatz % 2 == 0) {
			collatz /= 2;
			printf("%d\n", collatz);
		}
		else {
			collatz = (3 * collatz) + 1;
			printf("%d\n", collatz);
		}
		info.step_count++;
	}
	return info;
}



int main() {
	unsigned int val = 77031;
	printf("%d\n", val);
	Struct_uint result = uint_collatz_struct(val);
	printf("Number of Steps: %u\n", result.step_count);
	printf("Highest Step Reached: %u\n", result.max);
}
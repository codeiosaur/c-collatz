#include <stdio.h>
#include <limits.h>

#define L1_CACHE_SIZE = 32000 // amount of unsigned ints that can fit into my L1 CPU cache - change as needed

struct uintCollatzStepInfo {
	unsigned int step_count, max;
};

struct ulonglongCollatzStepInfo {
	unsigned long long step_count, max;
};

typedef struct uintCollatzStepInfo Struct_uint;
typedef struct ulonglongCollatzStepInfo Struct_ulonglong;

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
		} else {
			collatz = (3 * collatz) + 1;
		}
		printf("%u\n", collatz);
		info.step_count++;
	}
	return info;
}

Struct_ulonglong ulonglong_collatz_struct(unsigned long long collatz) {
	Struct_ulonglong info;
	info.max = 0;
	info.step_count = 0;
	while (collatz != 1) {
		if (collatz >= info.max) {
			info.max = collatz;
		}
		if (collatz % 2 == 0) {
			collatz /= 2;
		} else {
			collatz = (3 * collatz) + 1;
		}
		printf("%llu\n", collatz);
		info.step_count++;
	}
	return info;
}

void mass_uint_collatz(unsigned int end) {
	// used to find the point at which the uint function overflows - it overflows at 159,487
	for (unsigned int i = 2; i < end; i++) {
		unsigned int collatz = i;
		while (collatz != 1) {
			if (collatz % 2 == 0) {
				collatz /= 2;
			} else if ((3 * collatz + 1) < collatz) {
				printf("Error at %u, step %u!\n", i, collatz);
				return;
			} else {
				collatz = (3 * collatz) + 1;
			}
		}
	}
}

int main() {
	unsigned long long val = 989345275647;
	if (val < 159000) { // approximation
		printf("%u\n", val);
		Struct_uint result = uint_collatz_struct((unsigned int)val);
		printf("Number of Steps: %u\n", result.step_count);
		printf("Highest Step Reached: %u\n", result.max);
	} else {
		printf("%llu\n", val);
		Struct_ulonglong result = ulonglong_collatz_struct(val);
		printf("Number of Steps: %llu\n", result.step_count);
		printf("Highest Step Reached: %llu\n", result.max);
	}
	//printf("%u\n", 159487);
	//Struct_uint answer = uint_collatz_struct(159487);
	//printf("test: %d\n", answer);

	//unsigned int val = 77031;
	//Struct_uint result = uint_collatz_struct(val);
	//printf("%d\n", val);
	//printf("Number of Steps: %u\n", result.step_count);
	//printf("Highest Step Reached: %u\n", result.max);
}
#include <math.h>
#include <stdio.h>

#define L1_CACHE_SIZE 8192 // My l1 cache size/core is 64 KB, and one struct is 8 bytes. 8192 structs can fit - change as needed
#define L2_CACHE_SIZE 65536 // My l2 cache size/core is 512 KB - multiply l1 by 7

typedef struct ulonglongCollatzStepInfo {
	unsigned long long steps, max;
} Struct_ulonglong;

Struct_ulonglong ulonglong_collatz_struct(unsigned long long collatz) {
	// PRECONDITION: collatz > 0
	unsigned long long original_collatz = collatz;
	static Struct_ulonglong collatz_result[L2_CACHE_SIZE] = {{0, 0}}; // Array to optimize program by storing precalculated steps
	Struct_ulonglong info = { 0, collatz };
	
	while (collatz > 1) {
		if (collatz < L2_CACHE_SIZE && collatz_result[collatz].steps != 0) {
			info.steps += collatz_result[collatz].steps;
			if (collatz_result[collatz].max > info.max) {
				info.max = collatz_result[collatz].max;
			}
			break;
		}
		if (collatz % 2 == 0) {
			collatz /= 2;
		} else {
			collatz = (3 * collatz) + 1;
		}
		//printf("%llu\n", collatz);
		info.steps++;
		if (collatz >= info.max) {
			info.max = collatz;
		}
	}

	if (original_collatz < L2_CACHE_SIZE && collatz_result[original_collatz].steps == 0) {
		collatz_result[original_collatz] = info; // Cache the calculated steps for future use
	}
	return info;
}

void mass_uint_collatz(unsigned int end) {
	// used to find the point at which the uint function overflows - it overflows at 159,487
	for (unsigned int i = 2; i < end; i++) {
		unsigned int collatz = i;
		while (collatz > 1) {
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
	unsigned long long val1 = 16;
	Struct_ulonglong result = ulonglong_collatz_struct(val1);
	printf("%llu\n", val1);
	printf("Number of Steps: %llu\n", result.steps);
	printf("Highest Step Reached: %llu\n", result.max);

	unsigned long long val2 = 113383;
	result = ulonglong_collatz_struct(val2);
	printf("%llu\n", val2);
	printf("Number of Steps: %llu\n", result.steps);
	printf("Highest Step Reached: %llu\n", result.max);
	return 0;
}
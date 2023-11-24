#include <math.h>
#include <stdio.h>
#include <time.h>

#define L1_CACHE_SIZE 8192 // My l1 cache size/core is 64 KB, and one struct is 8 bytes. 8192 structs can fit - change as needed
#define L2_CACHE_SIZE 65536 // My l2 cache size/core is 512 KB - multiply l1 by 7
#define L3_CACHE_SIZE 8388608 // assuming 64 MB =  67,108,864 bytes
#define FINAL_CACHE 10000000 // 10^7

typedef struct ulonglongCollatzStepInfo {
	unsigned long long steps, max;
} Struct_ulonglong;

Struct_ulonglong ulonglong_collatz_struct(unsigned long long collatz) {
	// PRECONDITION: collatz > 0
	unsigned long long original_collatz = collatz;
	static Struct_ulonglong collatz_result[FINAL_CACHE] = {{0, 0}}; // Array to optimize program by storing precalculated steps
	Struct_ulonglong info = { 0, collatz };
	
	while (collatz > 1) {
		if (collatz < FINAL_CACHE && collatz_result[collatz].steps != 0) {
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
		if (collatz > info.max) {
			info.max = collatz;
		}
	}

	if (original_collatz < FINAL_CACHE && collatz_result[original_collatz].steps == 0) {
		collatz_result[original_collatz] = info; // Cache the calculated steps for future use
	}
	return info;
}

int main() {
	long double x = 10.0, y = 8.0;
	const long long MAX_BOUND = (long long)(powl(x, y) - 1);

	unsigned long long global_max_value = 0, global_max_steps = 0;
	Struct_ulonglong max_nums = { 1, 1 };

	bool conjecture_proving;
	printf("Do you want max integer and step count, or do you only want to prove the conjecture? (1 for former, 0 for latter)\n");

	clock_t t;
	t = clock();
	for (long long i = 1; i <= MAX_BOUND; i++) {
		Struct_ulonglong temp_struct = ulonglong_collatz_struct(i);
		if (temp_struct.max > global_max_value) {
			global_max_value = temp_struct.max;
			max_nums.steps = i;
		}
		if (temp_struct.steps > global_max_steps) {
			global_max_steps = temp_struct.steps;
			max_nums.max = i;
		}
	}

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
	printf("Highest step count from 1 to %llu: %llu, which has %llu steps\n", MAX_BOUND, max_nums.max, global_max_steps);
	printf("Highest max value during sequence from 1 to %llu: %llu, which reached %llu during its sequence\n", MAX_BOUND, max_nums.steps, global_max_value);
	printf("Time taken: %f seconds", time_taken);
	return 0;
}
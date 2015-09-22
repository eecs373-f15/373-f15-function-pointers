#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sort.h"

uint64_t rdtsc(){
	unsigned int lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}


void print_numbers(const int* numbers, unsigned count) {
	assert(count);

	unsigned i;
	printf("@ ");
	for (i=0; i < (count-1); i++) {
		printf("%d, ", numbers[i]);
	}
	printf("%d\n", numbers[i]);
}

uint64_t get_sorted_copy_and_effort(
		const int* numbers_in,
		int** numbers_out,
		unsigned count,
		sorting_fn sort) {
	*numbers_out = malloc(sizeof(int)*count);
	memcpy(*numbers_out, numbers_in, sizeof(int)*count);

	uint64_t before = rdtsc();
	sort(*numbers_out, count);
	uint64_t after = rdtsc();

	return after-before;
}


int main() {
	const int a[] = {1,115,-10,52,-6,2,4,264,23,-14,1,15,13,42,72,43,-143,53};
	const unsigned count = sizeof(a)/sizeof(int);

	sorting_fn* fn = sorting_fns;
	while (*fn != NULL) {
		uint64_t effort;
		int* list;

		printf("@ Calling sort %ld\n", fn-sorting_fns);
		effort = get_sorted_copy_and_effort(a, &list, count, *fn);
		fprintf(stderr, "# Q1: effort %"PRIu64"\n", effort);
		print_numbers(a, count);
		print_numbers(list, count);

		fn++;
	}

	unsigned char *data = (unsigned char*) bubble_sort;
	unsigned i;
	fprintf(stderr, "# Q2: Copy this output --> ");
#ifdef __clang__
	for (i=0x14; i < (0x14+5); i++) {
#else
	for (i=0; i < 8; i++) {
#endif
		fprintf(stderr, "%02x ", data[i]);
	}
	fprintf(stderr, "\n");

	return 0;
}

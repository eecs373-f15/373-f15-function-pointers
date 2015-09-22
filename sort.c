#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sort.h"

__attribute__ ((weak))
int compare(int a, int b) {
	    return a - b;
}

void bubble_sort(int *numbers, unsigned count) {
	int temp;
	int i, j;

	for(i = 0; i < count; i++) {
		for(j = 0; j < count - 1; j++) {
			if(compare(numbers[j+1], numbers[j]) < 0) {
				temp = numbers[j+1];
				numbers[j+1] = numbers[j];
				numbers[j] = temp;
			}
		}
	}
}

void insertion_sort(int *numbers, unsigned count) {
	int new[count];
	unsigned new_count = 0;

	while (new_count < count) {
		int num = numbers[new_count];

		unsigned idx = 0;
		while (true) {
			if (idx == new_count) {
				new[idx] = num;
				break;
			}

			if (compare(num, new[idx]) < 0) {
				unsigned i;
				for (i=new_count;i>idx;i--) {
					new[i] = new[i-1];
				}
				new[i] = num;
				break;
			}

			idx++;
		}

		new_count++;
	}

	memcpy(numbers, new, count*sizeof(int));
}

sorting_fn sorting_fns[] = {bubble_sort, insertion_sort, NULL};


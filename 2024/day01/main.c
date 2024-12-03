/**
 * @file aoc/2024/day01/main.c
 * The main routine and compile-time configuration macros.
 */

#include "main.h"

#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "compute.h"
#include "numlist.h"
#include "sizes.h"
#include "thread.h"

/**
 * Compares integers. I hate `qsort`.
 */
static int compare_ints(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

/**
 * Sorts global_data's various sublists and joins them into one long
 * list in global_data[0].
 */
static void sort_global_data(void)
{
	number_list_t *total;
	size_t i;

	total = &global_data[0];

	for (i = 0; i < NUMBER_LIST_COUNT; i++) {
		number_list_t *cur;

		int *left;
		int *right;

		cur = &global_data[i];

		qsort(cur->left_data, cur->left_len,
		      sizeof(int), &compare_ints);

		qsort(cur->right_data, cur->right_len,
		      sizeof(int), &compare_ints);

		if (cur == total)
			continue;

		left = &total->left_data[total->left_len];
		right = &total->right_data[total->right_len];

		memcpy(left, cur->left_data, cur->left_len * sizeof(int));
		total->left_len += cur->left_len;

		memcpy(right, cur->right_data, cur->right_len * sizeof(int));
		total->right_len += cur->right_len;
	}
}

/**
 * The main function.
 */
int main(int argc, char *argv[])
{
	pthread_t threads[THREAD_COUNT];
	thread_data_t chunks[THREAD_COUNT];

	long diff_sum;
	long sim_sum;

	size_t i;

	args_parse(argc, argv);

	sizes_calc();
	numlist_init(global_data, global_list_size);
	thread_init(threads, chunks);
	thread_free(threads, chunks);

	sort_global_data();

	compute_diff();
	compute_sim();

	diff_sum = 0;
	sim_sum = 0;

	for (i = 0; i < global_data[1].left_len; i++) {
		diff_sum += abs(global_data[1].left_data[i]);
		sim_sum += global_data[1].right_data[i];
	}

	printf("Differences: %ld\n", diff_sum);
	printf("Similarity value: %ld\n", sim_sum);

	return 0;
}

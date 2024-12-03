/**
 * @file aoc/2024/day01/compute.c
 * Computes the values of each part of the problem.
 */

#include "compute.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "main.h"
#include "numlist.h"
#include "thread.h"

/**
 * Computes the differences of the left and right lists. The result is
 * stored in global_data[1].left_data.
 */
void compute_diff(void)
{
	number_list_t *total;
	number_list_t *diff;

	size_t remaining;
	size_t size;

	size_t pos;
	size_t i;

	total = &global_data[0];
	diff = &global_data[1];

	if (total->left_len != total->right_len) {
		handle_error("sides don't match; invalid input data");
		exit(1);
	}

	remaining = total->left_len;
	size = (remaining + VECTOR_SIZE_INT - 1) / VECTOR_SIZE_INT;
	pos = 0;

	for (i = 0; i < size; i++) {
		size_t block_size;
		vec left;
		vec right;

		block_size = remaining % VECTOR_SIZE_INT;

		if (block_size == 0)
			block_size = VECTOR_SIZE_INT;

		memcpy(&left, &total->left_data[pos],
		       block_size * sizeof(int));

		memcpy(&right, &total->right_data[pos],
		       block_size * sizeof(int));

		left -= right;

		memcpy(&diff->left_data[pos], &left,
		       block_size * sizeof(int));

		pos += block_size;
		remaining -= block_size;
	}

	diff->left_len = total->left_len;
}

/**
 * Compute the similarity value between both lists. The result is stored
 * in global_data[1].right_data.
 */
void compute_sim(void)
{
	number_list_t *total;
	number_list_t *sim;
	
	size_t remaining;
	size_t size;

	size_t pos;
	size_t i;
	size_t j;

	total = &global_data[0];
	sim = &global_data[1];

	sim->right_len = total->right_len;
	memset(sim->right_data, 0, sim->right_len * sizeof(int));

	for (i = 0, j = 0; i < sim->right_len; i++) {
		int start_j;

		while (total->right_data[j] < total->left_data[i])
			j++;

		if (total->right_data[j] > total->left_data[i])
			continue;
		
		start_j = j;

		while (total->right_data[j++] == total->left_data[i])
			sim->right_data[i]++;

		j = start_j;
	}

	remaining = total->left_len;
	size = (remaining + VECTOR_SIZE_INT - 1) / VECTOR_SIZE_INT;
	pos = 0;

	if (total->left_len != sim->right_len) {
		handle_error("sides don't match; invalid input data");
		exit(1);
	}

	for (i = 0; i < size; i++) {
		size_t block_size;
		vec left;
		vec right;

		block_size = remaining % VECTOR_SIZE_INT;

		if (block_size == 0)
			block_size = VECTOR_SIZE_INT;

		memcpy(&left, &total->left_data[pos],
		       block_size * sizeof(int));

		memcpy(&right, &sim->right_data[pos],
		       block_size * sizeof(int));
		
		left *= right;

		memcpy(&sim->right_data[pos], &left,
		       block_size * sizeof(int));

		pos += block_size;
		remaining -= block_size;
	}
}

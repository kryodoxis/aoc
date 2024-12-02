/**
 * @file aoc/2024/day1/lists.c
 * Structures and routines for handling lists of numbers.
 */

#include "numlist.h"

#include <stddef.h>
#include <stdlib.h>

#include "error.h"

/**
 * Initializes `lists` with integer lists of size `size`.
 */
void numlist_init(number_list_t *lists, size_t size)
{
	size_t i;

	for (i = 0; i < NUMBER_LIST_COUNT; i++) {
		lists[i].left_data = malloc(size);

		if (lists[i].left_data == NULL) {
			handle_error("failed to allocate memory\n");
			exit(1);
		}

		lists[i].right_data = malloc(size);

		if (lists[i].right_data == NULL) {
			handle_error("failed to allocate memory\n");
			exit(1);
		}

		lists[i].left_len = 0;
		lists[i].right_len = 0;
	}
}

/**
 * Frees the integer lists in `lists`.
 */
void numlist_free(number_list_t *lists)
{
	size_t i;

	for (i = 0; i < NUMBER_LIST_COUNT; i++) {
		free(lists[i].left_data);
		free(lists[i].right_data);
	}
}

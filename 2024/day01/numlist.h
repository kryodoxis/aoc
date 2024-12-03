/**
 * @file aoc/2024/day01/numlist.h
 * Structures and routines for handling lists of numbers.
 */

#ifndef NUMLIST_H
#define NUMLIST_H

#include <stddef.h>

/**
 * The number of number lists, just because I feel wrong hardcoding it.
 * This is just 10. We live in a base 10 world, get used to it.
 */
#define NUMBER_LIST_COUNT 10

/**
 * Represents a list of numbers.
 */
typedef struct number_list {
	int *left_data;
	int *right_data;

	size_t left_len;
	size_t right_len;
} number_list_t;

/**
 * Initializes `lists` with integer lists of size `size`.
 */
void numlist_init(number_list_t *lists, size_t size);

/**
 * Frees the integer lists in `lists`.
 */
void numlist_free(number_list_t *lists);

#endif /* NUMLIST_H */

/**
 * @file aoc/2024/day03/sizes.h
 * Sizes of various data structures.
 */

#include "sizes.h"

#include <stddef.h>

#include "file.h"

/**
 * The number of lines handled by each thread.
 */
long thread_chars;

/**
 * Divide the file into thread-sized chunks.
 */
void sizes_calc(void)
{
	thread_chars = ((file_size + THREAD_COUNT - 1) / THREAD_COUNT);
}

/**
 * @file aoc/2024/day02/sizes.h
 * Sizes of various data structures.
 */

#include "sizes.h"

#include <stddef.h>

#include "file.h"

/**
 * The number of lines handled by each thread.
 */
long thread_lines;

/**
 * Divide the file into thread-sized chunks.
 */
void sizes_calc(void)
{
	thread_lines = ((file_lines.count + THREAD_COUNT - 1)
	                / THREAD_COUNT);
}

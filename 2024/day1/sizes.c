/**
 * @file aoc/2024/day1/sizes.h
 * Sizes of various data structures.
 */

#include "sizes.h"

#include <stddef.h>

#include "file.h"
#include "main.h"

/**
 * Total lines in the file.
 */
long total_lines;

/**
 * The number of lines handled by each thread.
 */
long thread_lines;

/**
 * The size of the global list.
 */
size_t global_list_size;

/**
 * The size of each thread's local list.
 */
size_t local_list_size;

/**
 * Divide the file into thread-sized chunks.
 */
void sizes_calc(void)
{
	total_lines = file_size / LINE_LENGTH;
	thread_lines = (total_lines + THREAD_COUNT - 1) / THREAD_COUNT;
	global_list_size = total_lines * sizeof(int);
	local_list_size = thread_lines * sizeof(int);
}

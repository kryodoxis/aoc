/**
 * @file aoc/2024/day1/sizes.h
 * Sizes of various data structures.
 */

#ifndef SIZES_H
#define SIZES_H

#include <stddef.h>

/**
 * Total lines in the file.
 */
extern long total_lines;

/**
 * The number of lines handled by each thread.
 */
extern long thread_lines;

/**
 * The size of the global list.
 */
extern size_t global_list_size;

/**
 * The size of each thread's local list.
 */
extern size_t local_list_size;

/**
 * Divide the file into thread-sized chunks.
 */
void sizes_calc(void);

#endif /* SIZES_H */

/**
 * @file aoc/2024/day02/sizes.h
 * Sizes of various data structures.
 */

#ifndef SIZES_H
#define SIZES_H

#include <stddef.h>

/**
 * The number of lines handled by each thread.
 */
extern long thread_lines;

/**
 * Divide the file into thread-sized chunks.
 */
void sizes_calc(void);

#endif /* SIZES_H */

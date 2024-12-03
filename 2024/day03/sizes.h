/**
 * @file aoc/2024/day03/sizes.h
 * Sizes of various data structures.
 */

#ifndef SIZES_H
#define SIZES_H

#include <stddef.h>

/**
 * The number of lines handled by each thread.
 */
extern long thread_chars;

/**
 * Divide the file into thread-sized chunks.
 */
void sizes_calc(void);

#endif /* SIZES_H */

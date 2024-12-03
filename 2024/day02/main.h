/**
 * @file aoc/2024/day02/main.h
 * The main routine and compile-time configuration macros.
 */

#ifndef MAIN_H
#define MAIN_H

/**
 * The number of threads to use when parsing the input file. Because
 * this is an extremely simple operation, I only use 4 here; it seems to
 * work fine for me.
 */
#define THREAD_COUNT 4

/**
 * The number of lines to make space for.
 */
#define LINES_COUNT 1000

/**
 * Define the SIMD vector size. This is in terms of sizeof(int), NOT in
 * terms of bytes, so be careful!
 */
#define VECTOR_SIZE_INT 16

/**
 * The REAL SIMD vector size. DO NOT CHANGE THIS!
 */
#define VECTOR_SIZE_REAL VECTOR_SIZE_INT * sizeof(int)

/**
 * The actual SIMD vector type.
 */
typedef int vec __attribute__ ((vector_size (VECTOR_SIZE_REAL)));

#endif /* MAIN_H */

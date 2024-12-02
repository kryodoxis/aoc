/**
 * @file aoc/2024/day1/main.h
 * The main routine and compile-time configuration macros.
 */

#ifndef MAIN_H
#define MAIN_H

/**
 * The size of each number. In my input set, they're all 5 digits, i.e.
 * the length of each string is 5 characters (excluding the terminator)
 * the floor of the base-10 logarithm of each number is 5 - 1.
 */
#define NUMBER_SIZE 5

/**
 * The size of the gap between numbers. In my input set, this is always
 * 3 spaces. This allows me to speed up these computations immensely.
 */
#define GAP_SIZE 3

/**
 * The number of threads to use when parsing the input file. Because
 * this is an extremely simple operation, I only use 4 here; it seems to
 * work fine for me.
 */
#define THREAD_COUNT 4

/**
 * The computed line length. Assume `\n` and not `\r\n`.
 */
#define LINE_LENGTH (NUMBER_SIZE + GAP_SIZE + NUMBER_SIZE + 1)

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

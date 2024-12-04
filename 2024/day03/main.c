/**
 * @file aoc/2024/day03/main.c
 * The main routine and compile-time configuration macros.
 */

#include "main.h"

#include <pthread.h>
#include <stdio.h>

#include "args.h"
#include "file.h"
#include "sizes.h"
#include "thread.h"

/**
 * The main function.
 */
int main(int argc, char *argv[])
{
	pthread_t threads[THREAD_COUNT];
	thread_data_t chunks[THREAD_COUNT];

	args_parse(argc, argv);

	sizes_calc();
	thread_init(threads, chunks);
	thread_free(threads);

	printf("Basic sum: %d\n", global_basic_sum);
	printf("Complex sum: %d\n", global_complex_sum);

	return 0;
}

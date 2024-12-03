/**
 * @file aoc/2024/day02/main.c
 * The main routine and compile-time configuration macros.
 */

#include "main.h"

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

	int i;

	args_parse(argc, argv);

	sizes_calc();
	thread_init(threads, chunks);
	thread_free(threads);

	printf("Chunk sum: %d\n", global_chunk_sum);
	printf("Damp sum: %d\n", global_damp_sum);

	return 0;
}

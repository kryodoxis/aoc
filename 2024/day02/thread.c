/**
 * @file aoc/2024/day02/thread.c
 * Threading routines and data structures.
 */

#include "thread.h"

#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "main.h"
#include "sizes.h"

/**
 * The global chunk sum (part 1.)
 */
int global_chunk_sum;

/**
 * The global damp sum (part 2.)
 */
int global_damp_sum;

/**
 * The mutex which controls the global safe line count.
 */
pthread_mutex_t global_lock;

/**
 * Reads a number given the line number and a mutable position. This is
 * a mess, but I don't want to rewrite it.
 */
static int read_number(int line_no, int *pos)
{
	int n;
	char *line;
	char *next;

	n = 0;
	line = file_lines.data[line_no];
	next = strchr(&line[*pos], ' ');

	if (next == NULL) {
		next = strchr(line, 0);

		if (&line[*pos] == next)
			return -1;
	}

	while (&line[*pos] < next) {
		n *= 10;
		n += line[(*pos)++] - '0';
	}

	if (*next != 0)
		(*pos)++;

	return n;
}

/**
 * Validates a chunk to be safe according to the problem specification.
 */
static int validate_chunk(vec chunk, int size)
{
	size_t i;

	vec shift;
	vec mask;
	vec spare;

	vec zero;
	vec three;

	/* hopefully just compiles to a broadcast */

	memset(&zero, 0, size * sizeof(int));
	three = zero + 3;

	for (i = 0; i < size; i++)
		mask[i + 1] = i;

	shift = __builtin_shuffle(chunk, mask);
	shift[0] = chunk[0];
	shift = chunk - shift;

	/* if it has a 0, return 0. this _should_ optimize into:
	 *   vptest xmm0,xmm0
	 *   jz [return 0] */

	spare = shift == zero;
	spare[0] = 0;

	if (memcmp(&spare, &zero, size * sizeof(int)) != 0)
		return 0;

	/* make sure they're all positive */

	if (shift[1] < 0)
		shift = -shift;

	/* make sure differences are no larger than 3 */

	spare = shift > three;
	spare[0] = 0;

	if (memcmp(&spare, &zero, size * sizeof(int)) != 0)
		return 0;

	/* make sure there isn't a mix of inc/dec */

	spare = shift < zero;
	spare[0] = 0;
	
	if (memcmp(&spare, &zero, size * sizeof(int)) != 0)
		return 0;

	/* safe! */

	return 1;
}

/**
 * Checks if a chunk WOULD be safe if one element were removed.
 */
static int validate_damp(vec chunk, int size)
{
	size_t i;
	size_t j;

	vec zero;
	memset(&zero, 0, size * sizeof(int));

	for (i = 0; i < size; i++) {
		vec spare;
		vec mask;

		for (j = 0; j < size; j++) {
			if (j >= i)
				mask[j] = j + 1;
			else
				mask[j] = j;
		}

		spare = __builtin_shuffle(chunk, mask);

		if (validate_chunk(spare, size - 1))
			return 0;
	}

	return 1;
}

/**
 * Initializes the threads after calculating the relevant values.
 */
void thread_init(pthread_t *threads, thread_data_t *chunks)
{
	size_t pos;
	size_t i;

	global_chunk_sum = 0;
	global_damp_sum = 0;

	pos = 0;

	for (i = 0; i < THREAD_COUNT; i++) {
		chunks[i].line_start = pos;

		pos += thread_lines;

		if (pos > file_lines.count)
			pos = file_lines.count;

		chunks[i].line_end = pos;

		pthread_create(&threads[i], NULL, &thread_main,
		               &chunks[i]);
	}
}

/**
 * Waits for the threads to terminate and frees the data that's been
 * consumed/moved by them (i.e. the number lists and the file data).
 */
void thread_free(pthread_t *threads)
{
	size_t i;

	for (i = 0; i < THREAD_COUNT; i++)
		pthread_join(threads[i], NULL);

	free(file_data);
}

/**
 * Each thread's main function. `ptr` is actually of type
 * `thread_data_t *`.
 */
void *thread_main(void *ptr)
{
	thread_data_t *data;

	int line;
	int pos;
	int size;

	int i;
	int done;

	int chunk_sum;
	int damp_sum;
	int chunk_keep;
	int damp_keep;
	
	data = ptr;

	line = data->line_start;
	pos = 0;
	size = 0;

	i = 0;

	chunk_sum = 0;
	damp_sum = 0;
	chunk_keep = 1;
	damp_keep = 0;

	while (line < data->line_end) {
		vec chunk;

		/* load the line into a vector. GCC unroll this loop
		 * and my life is yours */

		done = 0;
		size = VECTOR_SIZE_INT;

		for (; i < VECTOR_SIZE_INT; i++) {
			int n;

			n = read_number(line, &pos);

			if (n < 0) {
				size = i;
				done = 1;

				break;
			}

			chunk[i] = n;
		}


		/* if we're done and the chunk is ok, then continue */

		if (done) {
			int is_safe = validate_chunk(chunk, size);
		
			/* full chunk is safe */

			if (chunk_keep && is_safe) {
				chunk_sum++;
				damp_sum++;
			}

			/* full chunk is unsafe, but damp sum is safe */

			else {
				damp_keep += validate_damp(chunk, size);

				if (damp_keep == 0)
					damp_sum++;
			}

			/* continue to next line */

			goto reset_line;
		}

		/* if we're not done, continue */
		
		else {
			vec mask;

			/* total chunk is unsafe, discard it */

			if (!validate_chunk(chunk, size))
				chunk_keep = 0;

			/* damp sum MAY be safe, check for it! */

			damp_keep += validate_damp(chunk, size);

			mask[0] = VECTOR_SIZE_INT - 1;
			mask[1] = VECTOR_SIZE_INT - 2;

			chunk = __builtin_shuffle(chunk, mask);

			i = 2; /* start reading at 2 */
			continue;
		}

		/* just in case */
		continue;

		/* move to a new line */
	reset_line:
		i = 0;
		pos = 0;

		chunk_keep = 1;
		damp_keep = 0;

		line++;
	}

	pthread_mutex_lock(&global_lock);
	global_chunk_sum += chunk_sum;
	global_damp_sum += damp_sum;
	pthread_mutex_unlock(&global_lock);

	return NULL;
}

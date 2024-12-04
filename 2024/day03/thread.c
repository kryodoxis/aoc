/**
 * @file aoc/2024/day03/thread.c
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
 * The global basic (part 1) sum.
 */
int global_basic_sum;

/**
 * The global complex (part 2) sum.
 */
int global_complex_sum;

/**
 * The mutex which controls the global safe line count.
 */
pthread_mutex_t global_lock;

/**
 * Returns the next do() or don't() call.
 */
static char *next_do(char *ptr, int *flag)
{
	char *a;
	char *b;

	a = strstr(ptr, "do()");
	b = strstr(ptr, "don't()");

	if (!b || a < b) {
		if (flag)
			*flag = 1;

		return a;
	}

	else {
		if (flag)
			*flag = 0;

		return b;
	}
}

/**
 * Initializes the threads after calculating the relevant values.
 */
void thread_init(pthread_t *threads, thread_data_t *chunks)
{
	size_t pos;
	size_t i;

	global_basic_sum = 0;
	global_complex_sum = 0;

	pos = 0;

	for (i = 0; i < THREAD_COUNT; i++) {
		chunks[i].char_start = pos;

		pos += thread_chars;

		if (pos > file_size)
			pos = file_size;

		chunks[i].char_end = pos;

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

	char *next;
	char *pos;
	char *end;

	int flag_cur;
	int flag_next;

	int basic_sum;
	int complex_sum;

	data = ptr;

	if (data->char_start == 0)
		flag_cur = 1;
	
	if (data->char_start == 0)
		pos = file_data;
	else
		pos = next_do(&file_data[data->char_start], &flag_cur);

	next = next_do(pos, &flag_next);
	pos = strstr(pos, "mul(");
	end = next_do(&file_data[data->char_end], NULL);

	if (end == NULL)
		end = &file_data[data->char_end];

	basic_sum = 0;
	complex_sum = 0;

	/* there's actually a much faster way of doing this. we can 
	 * load characters into SIMD vectors and use bit masks, then
	 * ANDing them to find either substrings (series of 1s) or
	 * possible substrings we need to investigate (1s at end).
	 * 
	 * unfortunately, this is complex, and I'm too lazy to implement
	 * it. also, I'm not sure it'd lead to large enough an increase
	 * in performance to make it worth it. so I use the naive
	 * algorithm (with no caching, even!) */

	while (pos && pos < end) {
		int n;
		int k;

		while (next && pos > next) {
			pos = strstr(next, "mul(");

			if (pos == NULL)
				goto sync_data;

			flag_cur = flag_next;
			next = next_do(pos, &flag_next);
		}
		
		n = 0;
		k = 0;
		pos += 4;

		while (*pos && isdigit(*pos)) {
			n *= 10;
			n += *pos++ - '0';
		}

		if (n == 0 || *pos++ != ',')
			goto next_iter;
		
		while (*pos && isdigit(*pos)) {
			k *= 10;
			k += *pos++ - '0';
		}

		if (k == 0 || *pos++ != ')')
			goto next_iter;

		basic_sum += n * k;
		complex_sum += n * k * flag_cur;

	next_iter:
		pos = strstr(pos, "mul(");
	}

sync_data:
	pthread_mutex_lock(&global_lock);
	global_basic_sum += basic_sum;
	global_complex_sum += complex_sum;
	pthread_mutex_unlock(&global_lock);

	return NULL;
}

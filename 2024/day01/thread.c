/**
 * @file aoc/2024/day01/thread.c
 * Threading routines and data structures.
 */

#include "thread.h"

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "main.h"
#include "numlist.h"
#include "sizes.h"

/**
 * The global number lists.
 */
number_list_t global_data[NUMBER_LIST_COUNT];

/**
 * The mutex which controls the global number list.
 */
pthread_mutex_t global_lock;

/**
 * Reads a number given `thread_data_t`.
 */
static int read_number(thread_data_t *data)
{
	int n;
	int i;

	n = 0;

	/* GCC, unroll this loop and my life is yours */

	for (i = 0; i < NUMBER_SIZE; i++) {
		n *= 10;
		n += *data->data_start++ - '0';
	}

	return n;
}

/**
 * Sync `thread_data_t` with the global data.
 */
static void sync_data(thread_data_t *data)
{
	size_t i;

	pthread_mutex_lock(&global_lock);

	for (i = 0; i < NUMBER_LIST_COUNT; i++) {
		number_list_t *global_cur;
		number_list_t *local_cur;

		int *left;
		int *right;
		
		global_cur = &global_data[i];
		local_cur = &data->number_lists[i];

		left = &global_cur->left_data[global_cur->left_len];
		right = &global_cur->right_data[global_cur->right_len];

		memcpy(left, local_cur->left_data,
		       local_cur->left_len * sizeof(int));

		memcpy(right, local_cur->right_data,
		       local_cur->right_len * sizeof(int));

		global_cur->left_len += local_cur->left_len;
		global_cur->right_len += local_cur->right_len;
	}

	pthread_mutex_unlock(&global_lock);
}

/**
 * Initializes the threads after calculating the relevant values.
 */
void thread_init(pthread_t *threads, thread_data_t *chunks)
{
	char *pos;
	size_t i;

	pos = file_data;

	for (i = 0; i < THREAD_COUNT; i++) {
		chunks[i].data_start = pos;

		pos += thread_lines * LINE_LENGTH;

		if (pos > &file_data[file_size])
			pos = &file_data[file_size];

		chunks[i].data_end = pos;

		numlist_init(chunks[i].number_lists, local_list_size);

		pthread_create(&threads[i], NULL, &thread_main,
		               &chunks[i]);
	}

}

/**
 * Waits for the threads to terminate and frees the data that's been
 * consumed/moved by them (i.e. the number lists and the file data).
 */
void thread_free(pthread_t *threads, thread_data_t *chunks)
{
	size_t i;

	for (i = 0; i < THREAD_COUNT; i++) {
		pthread_join(threads[i], NULL);
		numlist_free(chunks[i].number_lists);
	}

	free(file_data);
}

/**
 * Each thread's main function. `ptr` is actually of type
 * `thread_data_t *`.
 */
void *thread_main(void *ptr)
{
	thread_data_t *data;

	data = ptr;

	while (data->data_start < data->data_end) {
		int c;
		int n;
		number_list_t *cur;

		c = *data->data_start - '0';
		n = read_number(data);

		cur = &data->number_lists[c];
		cur->left_data[cur->left_len++] = n;

		data->data_start += GAP_SIZE;

		c = *data->data_start - '0';
		n = read_number(data);

		cur = &data->number_lists[c];
		cur->right_data[cur->right_len++] = n;

		data->data_start++;
	}

	sync_data(data);
	return NULL;
}

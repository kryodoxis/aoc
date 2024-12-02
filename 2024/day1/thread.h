/**
 * @file aoc/2024/day1/thread.h
 * Threading routines and data structures.
 */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stddef.h>

#include "numlist.h"

/**
 * Represents the data (a 'chunk') a single thread processes. Contains
 * 10 number lists; number_lists[0] is a list of numbers starting in 0,
 * number_lists[1] is a list of numbers starting in 1, etc.
 */
typedef struct thread_data {
	char *data_start;
	char *data_end;
	
	struct number_list number_lists[NUMBER_LIST_COUNT];
} thread_data_t;

/**
 * The global number lists.
 */
extern number_list_t global_data[NUMBER_LIST_COUNT];

/**
 * The mutex which controls the global number list.
 */
extern pthread_mutex_t global_lock;

/**
 * Initializes the threads after calculating the relevant values.
 */
void thread_init(pthread_t *threads, thread_data_t *chunks);

/**
 * Waits for the threads to terminate and frees the data that's been
 * consumed/moved by them (i.e. the number lists and the file data).
 */
void thread_free(pthread_t *threads, thread_data_t *chunks);

/**
 * Each thread's main function. `ptr` is actually of type
 * `thread_data_t *`.
 */
void *thread_main(void *ptr);

#endif /* THREAD_H */

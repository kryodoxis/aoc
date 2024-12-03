/**
 * @file aoc/2024/day03/thread.h
 * Threading routines and data structures.
 */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stddef.h>

/**
 * Represents the data (a 'chunk') a single thread processes.
 */
typedef struct thread_data {
	size_t char_start;
	size_t char_end;

	int count;
} thread_data_t;

/**
 * The global sum.
 */
extern int global_sum;

/**
 * The mutex which controls the global safe line count.
 */
extern pthread_mutex_t global_lock;

/**
 * Initializes the threads after calculating the relevant values.
 */
void thread_init(pthread_t *threads, thread_data_t *chunks);

/**
 * Waits for the threads to terminate and frees the data that's been
 * consumed/moved by them (i.e. the file data).
 */
void thread_free(pthread_t *threads);

/**
 * Each thread's main function. `ptr` is actually of type
 * `thread_data_t *`.
 */
void *thread_main(void *ptr);

#endif /* THREAD_H */

/**
 * @file aoc/2024/day1/error.h
 * Error handling module.
 */

#ifndef ERROR_H
#define ERROR_H

/**
 * Handles an error thrown by the OS. Does NOT exit--the caller is
 * responsible for gracefully terminating the program.
 */
void handle_error(const char *message, ...);

#endif /* ERROR_H */

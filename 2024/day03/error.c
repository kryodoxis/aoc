/**
 * @file aoc/2024/day03/error.c
 * Error handling module.
 */

#include "error.h"

#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**
 * Handles an error thrown by the OS. Does NOT exit--the caller is
 * responsible for gracefully terminating the program.
 */
void handle_error(const char *message, ...)
{
	va_list args;
	char *error_message;

	va_start(args, message);
	error_message = strerror(errno);

	fputs("ERROR: ", stderr);
	vfprintf(stderr, message, args);
	fputc('\n', stderr);

	if (error_message != NULL)
		fprintf(stderr, "SYSTEM: %s\n", error_message);
}

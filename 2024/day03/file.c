/**
 * @file aoc/2024/day03/file.h
 * File IO module/wrapper.
 */

#include "file.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

/**
 * The file data.
 */
char *file_data;

/**
 * The file size.
 */
long file_size;

/**
 * Opens and reads a file. Returns 0 on success and 1 on failure. The
 * resultant file content and its size are located in `file_data` and
 * `file_size`, respectively; the former needs to be `free`d.
 */
void file_open(char *filename)
{
	FILE *file_ptr;
	int result;

	file_ptr = fopen(filename, "r");

	if (file_ptr == NULL) {
		handle_error("failed to open file %s", filename);
		exit(1);
	}

	result = fseek(file_ptr, 0, SEEK_END);
	file_size = ftell(file_ptr);
	result = result ? 1 : fseek(file_ptr, 0, SEEK_SET);

	if (result != 0 || file_size == -1L) {
		handle_error("failed to get size of %s", filename);
		exit(1);
	}

	file_data = malloc(file_size + 1);

	if (file_data == NULL) {
		handle_error("failed to alloc memory for %s", filename);
		exit(1);
	}

	fread(file_data, 1, file_size, file_ptr);

	if (ferror(file_ptr)) {
		handle_error("failed to read file %s", filename);
		exit(1);
	}

	file_data[file_size] = 0;
	fclose(file_ptr);
}

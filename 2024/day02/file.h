/**
 * @file aoc/2024/day02/file.h
 * File IO module/wrapper.
 */

#ifndef FILE_H
#define FILE_H

#include <stddef.h>
#include <stdio.h>

#include "main.h"

/**
 * The file data.
 */
extern char *file_data;

/**
 * The file size.
 */
extern long file_size;

/**
 * A list of lines in the file.
 */
extern struct file_lines {
	size_t count;
	char *data[LINES_COUNT];
} file_lines;

/**
 * Opens and reads a file. Returns 0 on success and 1 on failure. The
 * resultant file content and its size are located in `file_data` and
 * `file_size`, respectively.
 */
void file_open(char *filename);

/**
 * Parses `file_data` into a list of lines.
 */
void file_parse(void);

#endif /* FILE_H */

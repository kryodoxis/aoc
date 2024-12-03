/**
 * @file aoc/2024/day03/file.h
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
 * Opens and reads a file. Returns 0 on success and 1 on failure. The
 * resultant file content and its size are located in `file_data` and
 * `file_size`, respectively.
 */
void file_open(char *filename);

#endif /* FILE_H */

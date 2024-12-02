/**
 * @file aoc/2024/day1/args.c
 * Argument parsing.
 */

#include "args.h"

#include <stdio.h>
#include <stdlib.h>

#include "file.h"

/**
 * Parses command line arguments.
 */
void args_parse(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s INFILE\n", argv[0]);
		exit(0);
	}

	file_open(argv[1]);
}

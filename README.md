# Advent of Code

This repository contains all of my Advent of Code solutions. I write
them primarily in C, often using SIMD vectorization intrinsics to help.
They comply to ANSI C89 and POSIX 1c with GNU vectorization extensions
added.

Every solution should compile with `gcc *.c -std=c89 -Wpedantic -Wall`.
On many machines you will have to manually link with `pthreads`/`math`.

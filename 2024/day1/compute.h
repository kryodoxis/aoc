/**
 * @file aoc/2024/day1/compute.h
 * Computes the values of each part of the problem.
 */

#ifndef COMPUTE_H
#define COMPUTE_H

/**
 * Computes the differences of the left and right lists. The result is
 * stored in global_data[1].left_data.
 */
void compute_diff(void);

/**
 * Compute the similarity value between both lists. The result is stored
 * in global_data[1].right_data.
 */
void compute_sim(void);

#endif /* COMPUTE_H */
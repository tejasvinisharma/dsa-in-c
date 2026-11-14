#ifndef SORTING_H
#define SORTING_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Step 5: four ways to sort an array of `n` ints into ascending order,
 * in place. `n` can be 0 (then `a` may be NULL) and the array may hold
 * repeated values and negative numbers.
 */

/* Repeatedly swap neighbours that are out of order. Stop early if a
 * whole pass makes no swaps. */
void bubble_sort(int *a, size_t n);

/* For each position, find the smallest value in the rest of the array
 * and swap it into place. */
void selection_sort(int *a, size_t n);

/* Grow a sorted part on the left, inserting each new value into its
 * place by shifting bigger values one step right. */
void insertion_sort(int *a, size_t n);

/* Split in half, sort each half, then merge the two sorted halves.
 * It needs a temporary array: return false if malloc fails, true
 * otherwise. */
bool merge_sort(int *a, size_t n);

#endif

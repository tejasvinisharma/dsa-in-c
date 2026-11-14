#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

/*
 * Step 6: finding a value in an array of `n` ints.
 * `n` can be 0 (then `a` may be NULL).
 */

/* Check every value from the start. Return the index of the first one
 * equal to `key`, or -1 if there is none. Works on any array. */
long linear_search(const int *a, size_t n, int key);

/* `a` must already be sorted in ascending order. Halve the part of the
 * array you're searching each time, so it takes O(log n) steps.
 * Return the index of a value equal to `key` (any one of them, if it
 * appears more than once), or -1 if there is none. */
long binary_search(const int *a, size_t n, int key);

#endif

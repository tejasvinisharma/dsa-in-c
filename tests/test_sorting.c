#include <stdlib.h>
#include <string.h>

#include "sorting.h"
#include "test_util.h"

typedef void (*SortFunction)(int *a, size_t n);

static int compare_ints(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

/* Sorts a copy of `input` with `sort` and with the C library's qsort,
 * and returns true if the two results match. */
static bool sorts_correctly(SortFunction sort, const int *input, size_t n) {
    int mine[600], expected[600];
    memcpy(mine, input, n * sizeof(int));
    memcpy(expected, input, n * sizeof(int));
    sort(mine, n);
    qsort(expected, n, sizeof(int), compare_ints);
    return memcmp(mine, expected, n * sizeof(int)) == 0;
}

/* Runs one sorting function on every kind of input. */
static void check_all_cases(SortFunction sort) {
    sort(NULL, 0);                      /* empty: must not crash */
    CHECK(true);

    int one[] = {42};
    CHECK(sorts_correctly(sort, one, 1));

    int two[] = {2, 1};
    CHECK(sorts_correctly(sort, two, 2));

    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    CHECK(sorts_correctly(sort, sorted, 10));

    int reversed[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    CHECK(sorts_correctly(sort, reversed, 10));

    int repeats[] = {5, 3, 5, 1, 3, 5};
    CHECK(sorts_correctly(sort, repeats, 6));

    int negatives[] = {-3, 7, 0, -10, 7, 2};
    CHECK(sorts_correctly(sort, negatives, 6));

    int all_same[] = {4, 4, 4, 4};
    CHECK(sorts_correctly(sort, all_same, 4));

    /* 500 pseudo-random values from -1000 to 1000 (same every run). */
    int random_values[500];
    unsigned int seed = 12345;
    for (size_t i = 0; i < 500; i++) {
        seed = seed * 1103515245u + 12345u;
        random_values[i] = (int)((seed >> 16) % 2001) - 1000;
    }
    CHECK(sorts_correctly(sort, random_values, 500));
}

/* merge_sort returns bool, so wrap it to fit SortFunction. */
static bool merge_sort_returned_true = true;
static void merge_sort_wrapper(int *a, size_t n) {
    merge_sort_returned_true = merge_sort_returned_true && merge_sort(a, n);
}

static void test_bubble_sort(void) { check_all_cases(bubble_sort); }
static void test_selection_sort(void) { check_all_cases(selection_sort); }
static void test_insertion_sort(void) { check_all_cases(insertion_sort); }

static void test_merge_sort(void) {
    check_all_cases(merge_sort_wrapper);
    CHECK(merge_sort_returned_true);
}

int main(void) {
    RUN(test_bubble_sort);
    RUN(test_selection_sort);
    RUN(test_insertion_sort);
    RUN(test_merge_sort);
    FINISH("Step 5: sorting");
}

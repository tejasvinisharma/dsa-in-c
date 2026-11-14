#include "search.h"
#include "test_util.h"

static void test_linear_search(void) {
    CHECK(linear_search(NULL, 0, 5) == -1);     /* empty */

    int one[] = {5};
    CHECK(linear_search(one, 1, 5) == 0);
    CHECK(linear_search(one, 1, 6) == -1);

    int values[] = {4, 8, 4, 2};                /* not sorted: fine here */
    CHECK(linear_search(values, 4, 4) == 0);    /* first match */
    CHECK(linear_search(values, 4, 8) == 1);
    CHECK(linear_search(values, 4, 2) == 3);
    CHECK(linear_search(values, 4, 7) == -1);
}

static void test_binary_search_small_arrays(void) {
    CHECK(binary_search(NULL, 0, 5) == -1);     /* empty */

    int one[] = {5};
    CHECK(binary_search(one, 1, 5) == 0);
    CHECK(binary_search(one, 1, 4) == -1);      /* smaller than everything */
    CHECK(binary_search(one, 1, 6) == -1);      /* bigger than everything */

    int odd[] = {1, 3, 5, 7, 9, 11};
    bool finds_each = true;
    for (long i = 0; i < 6; i++) {
        finds_each = finds_each && binary_search(odd, 6, odd[i]) == i;
    }
    CHECK(finds_each);

    bool misses_each_gap = true;
    for (int key = 0; key <= 12; key += 2) {
        misses_each_gap = misses_each_gap && binary_search(odd, 6, key) == -1;
    }
    CHECK(misses_each_gap);
}

static void test_binary_search_with_repeats(void) {
    int repeats[] = {1, 2, 2, 2, 3};
    long index = binary_search(repeats, 5, 2);
    CHECK(index >= 1 && index <= 3);            /* any of the 2s is fine */
    CHECK(binary_search(repeats, 5, 4) == -1);
}

static void test_binary_search_large_array(void) {
    static int evens[10001];                    /* 0, 2, 4, ..., 20000 */
    for (int i = 0; i <= 10000; i++) {
        evens[i] = 2 * i;
    }
    bool finds_every_value = true;
    bool misses_every_gap = true;
    for (int i = 0; i <= 10000; i++) {
        finds_every_value =
            finds_every_value && binary_search(evens, 10001, 2 * i) == i;
        misses_every_gap =
            misses_every_gap && binary_search(evens, 10001, 2 * i + 1) == -1;
    }
    CHECK(finds_every_value);
    CHECK(misses_every_gap);
    CHECK(binary_search(evens, 10001, -1) == -1);
}

int main(void) {
    RUN(test_linear_search);
    RUN(test_binary_search_small_arrays);
    RUN(test_binary_search_with_repeats);
    RUN(test_binary_search_large_array);
    FINISH("Step 6: searching");
}

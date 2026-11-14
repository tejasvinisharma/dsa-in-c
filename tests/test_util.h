#ifndef TEST_UTIL_H
#define TEST_UTIL_H

/*
 * A tiny test helper, so the project needs nothing but a C compiler.
 *
 *   CHECK(condition)  counts a check, and prints the line if it fails
 *   RUN(test_name)    prints the test's name, then runs it
 *   FINISH("Step 1")  prints the score and ends main(): exit code 0 only
 *                     if every check passed
 */

#include <stdbool.h>
#include <stdio.h>

static int checks_run = 0;
static int checks_failed = 0;

#define CHECK(condition)                                                    \
    do {                                                                    \
        checks_run++;                                                       \
        if (!(condition)) {                                                 \
            checks_failed++;                                                \
            printf("  FAIL  %s line %d:  %s\n", __FILE__, __LINE__,         \
                   #condition);                                             \
        }                                                                   \
    } while (0)

#define RUN(test)                                                           \
    do {                                                                    \
        printf("%s\n", #test);                                              \
        fflush(stdout);                                                     \
        test();                                                             \
    } while (0)

#define FINISH(step_name)                                                   \
    do {                                                                    \
        printf("\n%s: %d of %d checks passed\n", step_name,                 \
               checks_run - checks_failed, checks_run);                     \
        return checks_failed == 0 ? 0 : 1;                                  \
    } while (0)

#endif

#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Starter-kit placeholder. Every function you haven't written yet calls
 * TODO(...), which prints a message and stops the program.
 *
 * When you write a function, delete its TODO line.
 * When every TODO line is gone, delete the #include "todo.h" line too.
 */
#define TODO(step, function_name)                                             \
    do {                                                                      \
        fprintf(stderr, "\nNot written yet: %s() (%s). See BUILD_GUIDE.md\n", \
                function_name, step);                                         \
        exit(2);                                                              \
    } while (0)

#endif

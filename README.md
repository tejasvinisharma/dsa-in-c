# Data Structures in C

Linked lists, stacks, queues, expression conversion, sorting and searching, written from scratch in C, with tests for each one. I'm building it alongside my data structures course (CSE205) at Lovely Professional University.

**Status:** in progress. A structure moves to "Done" when all of its tests pass.

| Step | Structure | Operations | Time complexity | Status |
|---|---|---|---|---|
| 1 | Singly linked list | push front, push back, pop front, insert at, find, remove, reverse | — | Not started |
| 2 | Stack (array and linked list) | push, pop, peek | — | Not started |
| 3 | Circular queue | enqueue, dequeue, peek | — | Not started |
| 4 | Infix to postfix, and postfix evaluation | convert, evaluate | — | Not started |
| 5 | Sorting | bubble, selection, insertion, merge | — | Not started |
| 6 | Searching | linear, binary | — | Not started |

## How to run it

You need `gcc` and `make`. On Windows, use the MSYS2 or Git Bash terminal (setup steps are in [BUILD_GUIDE.md](BUILD_GUIDE.md)).

```bash
git clone https://github.com/tejasvinisharma/dsa-in-c.git
cd dsa-in-c
make test      # every step, in order
make step1     # one step: step1 to step6
```

Each step prints a score such as `Step 1: linked list: 60 of 60 checks passed`.

## Project structure

```
src/
  linked_list.h   what each function must do (one header per structure)
  linked_list.c   the code
  ...             the same pair for stack, queue, expression, sorting, search
tests/
  test_util.h     a tiny CHECK() helper, so nothing needs installing
  test_*.c        the tests for each step
Makefile          make step1 ... make step6, make test
BUILD_GUIDE.md    the step-by-step plan
```

## What I learned

To be filled in as I finish each step.

## Credits

The folder layout, the header files, the tests and the build guide came from a starter kit I was given. The code inside the `.c` files in `src/` is my own.

## Author

**Tejasvini Sharma**, B.Tech CSE at Lovely Professional University
[LinkedIn](https://www.linkedin.com/in/tejasvinisharma) · [Portfolio](https://tejasvinisharma.github.io)
